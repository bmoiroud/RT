/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.cl                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoiroud <bmoiroud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/31 17:12:23 by bmoiroud          #+#    #+#             */
/*   Updated: 2018/01/08 16:32:22 by bmoiroud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h.cl"

static void			ft_cyl_col(const t_object obj, t_ray *ray)
{
	const t_vector		dist = ray->pos - obj.pos;
	const t_vector		rot = obj.rot;
	t_equation			e = {
		.a = dot(ray->dir, ray->dir) - pow(dot(ray->dir, rot), 2.0), \
		.b = 2 * (dot(ray->dir, dist) - dot(ray->dir, rot) * dot(dist, rot)), \
		.c = dot(dist, dist) - pow(dot(dist, rot), 2) - pow(obj.size.x, 2), \
		.delta = e.b * e.b - 4.0 * e.a * e.c
	};
	if (e.delta < 0.0)
		return ;
	e.c = (-e.b + sqrt(e.delta)) / (2 * e.a);
	e.delta = (-e.b - sqrt(e.delta)) / (2 * e.a);
	if (e.c > e.delta)
		e.c = e.delta;
	if (sqrt(pow(length(e.c * ray->dir + ray->pos - obj.pos), 2) - pow(obj.size.x, 2)) >= obj.size.y / 2 && obj.size.y >= 0.0)
        return ;
    if (e.c > 0.0000001 && e.c < ray->t)
		ray->t = e.c;
}
	
static double2		ft_cyl_text_coords(const t_vector hit, const __global t_object *obj, const t_ray *ray, __constant double *rand)
{
	const t_vector		n = (hit - obj->pos) - (obj->rot * (dot(ray->dir, obj->rot) * ray->dist + dot(ray->pos - obj->pos, obj->rot)));
	double2			c = {
		atan2(n.x, n.z), \
		hit.y + ((obj->p_texture == BRICKS) ? 100000 : 0)
	};
	
	c.x -= (c.x < 0.0) ? 1.0 : 0.0;
	c.x += (c.x > 1.0) ? 1.0 : 0.0;
	c.y -= (c.y < 0.0) ? 3.05 : 0.0;
	c.y += (c.y > 3.05) ? 3.05 : 0.0;
	return (fabs(c));
}