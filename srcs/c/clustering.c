/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clustering.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoiroud <bmoiroud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/17 16:04:15 by bmoiroud          #+#    #+#             */
/*   Updated: 2018/01/11 19:18:50 by bmoiroud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

long	init_client(char *host)
{
	struct sockaddr_in	serv_addr;
	struct hostent		*server;
	long				sockfd;
	int					ret;

	ret = 0;
	ft_bzero(&serv_addr, sizeof(struct sockaddr_in));
	server = NULL;
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	(sockfd < 0) ? errors(ERR_SYS, "Error, opening socket,") : 0;
	server = gethostbyname(host);
	(server == NULL) ? errors(ERR_SYS, "Error, no such host,") : 0;
	ft_bzero((char *)&serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	ft_strncpy((char *)&serv_addr.sin_addr.s_addr, (char *)server->h_addr, \
															server->h_length);
	serv_addr.sin_port = htons(PORT);
	ret = connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
	(ret < 0) ? errors(ERR_SYS, "Error connecting,") : 0;
	return (sockfd);
}

void	client(long sockfd)
{
	t_data		data;
	t_cluster	cluster;
	int			loop;
	int			i;

	ft_bzero(&data, sizeof(t_data));
	ft_bzero(&cluster, sizeof(t_cluster));
	read(sockfd, &loop, sizeof(int));
	read(sockfd, &data, sizeof(t_data));
	// print_struct(data.rt);
	cluster.size_x = WIN_W;
	cluster.size_y = WIN_H;
	if (!(cluster.pixels = ft_memalloc(BPP * cluster.size_x * cluster.size_y)))
		errors(ERR_SYS, 0);
	// cluster.size_x /= (data.rt.nb_cli + 1);
	cl_init(&data.cl, 0);
	while (loop)
	{
		if (loop == EVENT_UPDATE)
		{
			cl_run(&data.cl, (size_t[WORK_DIM]){cluster.size_y, cluster.size_x}, 4,\
				(t_arg){cluster.pixels, sizeof(uint32_t) * cluster.size_y * \
				cluster.size_x, CL_MEM_WRITE_ONLY}, \
				(t_arg){&data.rt, sizeof(t_rt), CL_MEM_READ_ONLY}, \
				(t_arg){&data.keys, sizeof(t_key), CL_MEM_READ_ONLY}, \
				(t_arg){&data.rand, MAX_RAND * sizeof(double), CL_MEM_READ_ONLY});
			i = -1;
			while (++i < cluster.size_x * cluster.size_y)
			{
				// printf("%d\t", cluster.pixels[i]);
				write(sockfd, &cluster.pixels[i], sizeof(uint32_t));
			}
		}
		printf("1\n");
		read(sockfd, &loop, sizeof(int));
		read(sockfd, &data, sizeof(t_data));
	}
	free(cluster.pixels);
	close(sockfd);
	cl_end(&data.cl);
}

void	init_server(t_server *server)
{
	if ((server->sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		errors(ERR_SYS, "Error opening socket\n");
	server->serv_addr.sin_family = AF_INET;
	server->serv_addr.sin_addr.s_addr = INADDR_ANY;
	server->serv_addr.sin_port = htons(PORT);
	if (bind(server->sockfd, (struct sockaddr *)&server->serv_addr, \
												sizeof(server->serv_addr)) < 0)
		errors(ERR_SYS, "Error on binding");
}

void	ft_get_img(t_server server, t_data *data, uint32_t *pixels, int nb_cli)
{
	int			i;
	int			j;
	int			size;

	i = -1;
	(void)data;
	size = BPP * WIN_W * WIN_H;
	while (++i < nb_cli)
	{
		j = -1;
		while ((j += (nb_cli + 1)) < WIN_W * WIN_H)
			read(server.clisock[i], &pixels[j], sizeof(uint32_t));
	}
}

void	ft_send_data(t_data data, t_server server, int nb_cli, int loop)
{
	int		i;

	i = -1;
	while (++i < nb_cli)
	{
		data.rt.offset = i + 1;
		write(server.clisock[i], &loop, sizeof(int));
		write(server.clisock[i], (void *)&data, sizeof(data));
	}
}

void	main_loop_clustering(t_data *data, int nb_cli, t_server server)
{
	int		loop;

	loop = 2;
	// data->sdl.size.x /= (nb_cli + 1);
	while (loop)
	{
		if (loop == EVENT_UPDATE)
		{
			ft_send_data(*data, server, nb_cli, loop);
			cl_run(&data->cl, (size_t[WORK_DIM]){data->sdl.size.y, \
			data->sdl.size.x}, 4, \
			(t_arg){data->sdl.draw_surface->pixels, sizeof(uint32_t) * \
			data->sdl.size.y * data->sdl.size.x, CL_MEM_WRITE_ONLY}, \
			(t_arg){&data->rt, sizeof(t_rt), CL_MEM_READ_ONLY}, \
			(t_arg){&data->keys, sizeof(t_key), CL_MEM_READ_ONLY}, \
			(t_arg){&data->rand, MAX_RAND * sizeof(double), CL_MEM_READ_ONLY});
			ft_get_img(server, data, data->sdl.draw_surface->pixels, nb_cli);
			sdl_run(&data->sdl);
		}
		loop = sdl_events(&data->sdl, &data->keys, &data->rt);
	}
}

void	server(t_data data, int nb_cli)
{
	t_server	server;
	int			i;

	i = -1;
	data.rt.nb_cli = nb_cli;
	data.sdl.size.x /= (nb_cli + 1);
	ft_bzero(&server, sizeof(t_server));
	init_server(&server);
	while (++i < nb_cli)
	{
		listen(server.sockfd, 5);
		server.clilen[i] = sizeof(server.cli_addr[i]);
		if ((server.clisock[i] = accept(server.sockfd, (struct sockaddr *)\
								&server.cli_addr[i], &server.clilen[i])) < 0)
			errors(ERR_SYS, "Error on accept\n");
	}
	sdl_init(&data.sdl, PROGRAM_NAME);
	cl_init(&data.cl, 0);
	main_loop_clustering(&data, nb_cli, server);
	cl_end(&data.cl);
	sdl_end(&data.sdl);
	i = -1;
	while (++i < NB_MAX_CLIENT)
		close(server.clisock[i]);
	close(server.sockfd);
}
