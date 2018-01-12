/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.cl                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoiroud <bmoiroud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/31 17:12:25 by bmoiroud          #+#    #+#             */
/*   Updated: 2017/12/15 18:09:01 by bmoiroud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h.cl"

static void			ft_cone_col(const t_object obj, t_ray *ray)
{
	const t_vector		dist = ray->pos - obj.pos;
	const t_vector		rot = obj.rot;
	t_equation			e = {
		.a = dot(ray->dir, ray->dir) - (1.0 + pow(tan(PI * (obj.size.x / 180.0)), 2.0)) * pow(dot(ray->dir, rot), 2.0), \
		.b = 2 * (dot(ray->dir, dist) - (1.0 + pow(tan(PI * (obj.size.x / 180.0)), 2.0)) * dot(ray->dir, rot) * dot(dist, rot)), \
		.c = dot(dist, dist) - (1.0 + pow(tan(PI * (obj.size.x / 180.0)), 2.0)) * pow(dot(dist, rot), 2.0), \
		.delta = e.b * e.b - 4.0 * e.a * e.c
	};

	if (e.delta < 0.0)
		return ;
	e.c = (-e.b + sqrt(e.delta)) / (2.0 * e.a);
	e.delta = (-e.b - sqrt(e.delta)) / (2.0 * e.a);
	if (e.c > e.delta)
		e.c = e.delta;
	if (e.c > 0.0000001 && e.c < ray->t)
		ray->t = e.c;
}

static double2		ft_cone_text_coords(const t_vector hit, const __global t_object *obj, const t_ray *ray, __constant double *rand)
{
	// const t_vector		hit = ray->pos + ray->t * ray->dir;
	// const t_vector		n = ft_normale(rt, obj, hit, ray, rand);
	// double2				c = {

	// };
	
	// c.x -= (c.x < 0.0) ? 1.0 : 0.0;
	// c.x += (c.x > 1.0) ? 1.0 : 0.0;
	// c.y -= (c.y < 0.0) ? 1.0 : 0.0;
	// c.y += (c.y > 1.0) ? 1.0 : 0.0;
	// return (fabs(c));
}