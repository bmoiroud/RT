/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.cl                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoiroud <bmoiroud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/31 17:12:20 by bmoiroud          #+#    #+#             */
/*   Updated: 2017/11/12 16:00:52 by bmoiroud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h.cl"

static void		ft_plane_col(const t_object obj, t_ray *ray)
{
	const double	d = (dot(obj.rot, obj.pos) - dot(obj.rot, ray->pos)) \
												/ dot(obj.rot, ray->dir);
	if (d > 0.0000001 && d < ray->t)
		ray->t = d;
}

static double2		ft_plane_text_coords(const t_vector hit, const __global t_object *obj)
{
	const t_vector	v1 = {obj->pos.x - 0.0000000000001, obj->pos.y, obj->pos.z};
	const t_vector	v2 = cross(v1, obj->rot);
	double2			c = {
		dot(hit, v1), \
		dot(hit, v2)
	};

	c.x -= (c.x < 0.0) ? 1.0 : 0.0;
	c.x += (c.x > 1.0) ? 1.0 : 0.0;
	c.y -= (c.y < 0.0) ? 1.0 : 0.0;
	c.y += (c.y > 1.0) ? 1.0 : 0.0;
	return (c);
}