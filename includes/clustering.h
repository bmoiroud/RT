/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clustering.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoiroud <bmoiroud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/18 19:34:34 by bmoiroud          #+#    #+#             */
/*   Updated: 2018/01/11 15:05:40 by bmoiroud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLUSTERING_H
# define CLUSTERING_H

# include	<stdio.h>
# include	<stdlib.h>
# include	<unistd.h>
# include	<string.h>
# include	<sys/types.h>
# include	<sys/socket.h>
# include	<netinet/in.h>
# include	<netdb.h> 
# include	<pthread.h>
# include	"get_next_line.h"

# define	PORT			4242
# define 	NB_MAX_CLIENT	4
# define	TIME_OUT		10

typedef struct	s_server
{
	struct sockaddr_in	serv_addr;
	struct sockaddr_in	cli_addr[NB_MAX_CLIENT];
	socklen_t 			clilen[NB_MAX_CLIENT];
	long				clisock[NB_MAX_CLIENT];
	long				sockfd;
}				t_server;

typedef struct		s_cluster
{
	int				size_x;
	int				size_y;
	uint32_t		*pixels;
	
}					t_cluster;

#endif