/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wood.cl                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoiroud <bmoiroud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/04 18:21:10 by bmoiroud          #+#    #+#             */
/*   Updated: 2018/01/08 18:10:27 by bmoiroud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h.cl"

static t_color		ft_wood(const t_vector hit, const __global t_object *obj, const t_vector n, __constant double *rand)
{
    return ((t_color){0, 0, 0, 0});
}