/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoiroud <bmoiroud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/23 15:07:34 by bmoiroud          #+#    #+#             */
/*   Updated: 2018/01/08 15:15:56 by bmoiroud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ft_init_data(t_data *data)
{
	t_rt	*rt;
	int		i;

	i = -1;
	rt = &data->rt;
	while (++i < rt->nb_obj)
		if (i < rt->nb_obj)
			rt->objects[i].rot = ft_norm_vector(rt->objects[i].rot);
	i = -1;
	while (++i < MAX_RAND)
		data->rand[i] = (double)rand() / (double)RAND_MAX;
	ft_calc_dir_vec(&data->rt.eye, data->rt.m);
}

void	ft_init_objs(t_rt *rt, int o, int l)
{
	while (++o < rt->nb_obj)
		rt->objects[o].color.c = -1;
	while (++l < rt->nb_light)
		rt->lights[l].intensity = -1;
}

void	ft_init_objects(char *file, t_rt *rt, int o, int l)
{
	char	*line;
	int		fd;
	int		i;

	i = 0;
	line = NULL;
	if ((fd = open(file, O_RDONLY)) == -1)
		ft_error(1, 0);
	while (get_next_line(fd, &line))
	{
		if (ft_objectid(line) < 4 && ft_objectid(line) > -1)
			rt->nb_obj++;
		else if (ft_objectid(line) == 4)
			rt->nb_light++;
		else if (ft_strcmp(line, "#") == 0)
			i++;
		free(line);
	}
	close(fd);
	if (i - 1 < rt->nb_light + rt->nb_obj)
		ft_error(2, 0);
	ft_init_objs(rt, o, l);
}

void	ft_init_struct(t_data *data)
{
	int		i;

	i = -1;
	ft_bzero(data, sizeof(t_data));
	while (++i < OBJS_MAX)
	{
		data->rt.objects[i].reflect = 0.0;
		data->rt.objects[i].refract = 0.0;
		data->rt.objects[i].transp = 0.0;
		data->rt.objects[i].spec = 1.0;
		data->rt.objects[i].size = (t_vector){ -1.0, -1.0, -1.0 };
	}
	i = -1;
	while (++i < LGTS_MAX)
		data->rt.lights[i].intensity = -1;
}
