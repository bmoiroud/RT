/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rand.cl                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoiroud <bmoiroud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/02 15:33:59 by bmoiroud          #+#    #+#             */
/*   Updated: 2017/12/14 16:00:18 by bmoiroud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h.cl"

static double		ft_rand(const int x)
{
	int	value = (x << 13) ^ x;

	value = (value * (value * value * 15731 + 789221) + 1376312589);
	return ((double)(value & 0x7fffffff) / 1073741824.0);
}

static double		ft_rand2(const int x, const int y)
{
	double	value = ft_rand(x);

	return (ft_rand(value + y) * 850000);
}

static double		ft_rand3(const int x, const int y, const int z)
{
	double	value = ft_rand(x);

	value = ft_rand(value + y) * 850000;
	return (ft_rand(value + z) * 850000);
}