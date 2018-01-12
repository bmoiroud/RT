/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.cl                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoiroud <bmoiroud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/13 19:43:00 by bmoiroud          #+#    #+#             */
/*   Updated: 2018/01/08 15:52:43 by bmoiroud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h.cl"
#include "sphere.cl"
#include "plane.cl"
#include "cone.cl"
#include "cylinder.cl"

static void		ft_check_collisions_2(__global t_rt *rt, __global t_light *l, t_ray *ray)
{
	int			i = -1;
	t_object	o;

	while (++i < rt->nb_light)
	{
		o.size.x = 0.3;
		o.pos = l[i].pos;
		ft_sphere_col(o, ray);
		if (ray->t < ray->dist)
		{
			ray->id = i + rt->nb_obj;
			ray->dist = ray->t;
		}
	}
}

static void		ft_check_collisions(__global t_rt *rt, t_ray *ray)
{
	int			i = -1;
	
	while (++i < rt->nb_obj)
	{
		if (rt->objects[i].type == SPHERE)
			ft_sphere_col(rt->objects[i], ray);
		else if (rt->objects[i].type == PLANE)
			ft_plane_col(rt->objects[i], ray);
		else if (rt->objects[i].type == CONE)
			ft_cone_col(rt->objects[i], ray);
		else if (rt->objects[i].type == CYLINDER)
			ft_cyl_col(rt->objects[i], ray);
		if (ray->t < ray->dist)
		{
			ray->id = i;
			ray->dist = ray->t;
		}
	}
	if (rt->lights)
		ft_check_collisions_2(rt, rt->lights, ray);
}
