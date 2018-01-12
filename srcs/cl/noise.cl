/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   noise.cl                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoiroud <bmoiroud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/31 16:25:06 by bmoiroud          #+#    #+#             */
/*   Updated: 2018/01/08 18:08:28 by bmoiroud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h.cl"
#include "rand.cl"

static double		ft_perlin(unsigned int i, const t_vector v)
	{
		const int		j = i & 0xf;
		const t_vector	grad[16] = {
			{1.0, 1.0, 0.0}, \
			{1.0, -1.0, 0.0}, \
			{-1.0, 1.0, 0.0}, \
			{-1.0, -1.0, 0.0}, \
			{1.0, 0.0, 1.0}, \
			{1.0, 0.0, -1.0}, \
			{-1.0, 0.0, 1.0}, \
			{-1.0, 0.0, -1.0}, \
			{0.0, 1.0, 1.0}, \
			{0.0, 1.0, -1.0}, \
			{0.0, -1.0, 1.0}, \
			{0.0, -1.0, -1.0}, \
			{1.0, 1.0, 0.0}, \
			{-1.0, 1.0, 0.0}, \
			{0.0, -1.0, 1.0}, \
			{0.0, -1.0, -1.0}
		};
		return (dot(v, normalize(grad[j])));
	}

	static double		ft_noise_weight(const double w)
	{
		return ((w * w * w * (w * (w * 6.0 - 15.0) + 10.0)));
	}

	static double		ft_interp(const double w, const double a, const double b)
	{
		return (mix(a, b, w));
	}

	static double		ft_noise(const t_vector hit, const int perm[256])
	{
		const t_vector		v1 = floor(hit);
		const t_vector		v2 = hit - v1;
		const t_vector		v3[7] = {
			{v2.x - 1.0, v2.y, v2.z}, \
			{v2.x, v2.y - 1.0, v2.z}, \
			{v2.x, v2.y, v2.z - 1.0}, \
			{v2.x - 1.0, v2.y - 1.0, v2.z}, \
			{v2.x - 1.0, v2.y, v2.z - 1.0}, \
			{v2.x, v2.y - 1.0, v2.z - 1.0}, \
			{v2.x - 1.0, v2.y - 1.0, v2.z - 1.0}
		};
		const int3			u1 = {
			(int)v1.x, \
			(int)v1.z, \
			(int)v1.y
		};
		const int3			u2 = u1 + 1;

		const unsigned int	p1 = perm[u1.x & 0xff];
		const unsigned int	p2 = perm[u2.x & 0xff];

		const unsigned int	p3 = perm[((p1 + u1.y) & 0xff)];
		const unsigned int	p4 = perm[((p2 + u1.y) & 0xff)];
		const unsigned int	p5 = perm[((p1 + u2.y) & 0xff)];
		const unsigned int	p6 = perm[((p2 + u2.y) & 0xff)];
		
		const unsigned int	p7 = perm[((p3 + u1.z) & 0xff)];
		const unsigned int	p8 = perm[((p4 + u1.z) & 0xff)];
		const unsigned int	p9 = perm[((p5 + u1.z) & 0xff)];
		const unsigned int	p10 = perm[((p6 + u1.z) & 0xff)];
		const unsigned int	p11 = perm[((p3 + u2.z) & 0xff)];
		const unsigned int	p12 = perm[((p4 + u2.z) & 0xff)];
		const unsigned int	p13 = perm[((p5 + u2.z) & 0xff)];
		const unsigned int	p14 = perm[((p6 + u2.z) & 0xff)];

		const double2		v4 = {
			ft_perlin(p7, v2), \
			ft_perlin(p8, v3[0])
		};
		const double2		v5 = {
			ft_perlin(p9, v3[1]), \
			ft_perlin(p10, v3[3])
		};
		const double2		v6 = {
			ft_perlin(p11, v3[2]), \
			ft_perlin(p12, v3[4])
		};
		const double2		v7 = {
			ft_perlin(p13, v3[5]), \
			ft_perlin(p14, v3[6])
		};
		const t_vector		w = {
			ft_noise_weight(v2.x), \
			ft_noise_weight(v2.y), \
			ft_noise_weight(v2.z)
		};
		
		return (ft_interp(w.z, \
					ft_interp(w.y, \
						ft_interp(w.x, v4.x, v4.y), \
						ft_interp(w.x, v5.x, v5.y)), \
					ft_interp(w.y, \
						ft_interp(w.x, v6.x, v6.y), \
						ft_interp(w.x, v7.x, v7.y)\
						) \
					) \
				);
	}

	static double		ft_perlin_noise(const __global t_object *obj, const t_vector hit)
	{
		const int	perm[256] = {
			151, 91, 90, 15, 131, 13, 201, 95, 96, 53, 194, 233, 7, 225, 99, 37,\
			8, 240, 21, 10, 23, 190, 6, 148, 247, 120, 234, 75, 0, 26, 160, 137, \
			35, 11, 32, 57, 177, 33, 88, 237, 149, 56, 87, 174, 20, 125, 136, 171, \
			134, 139, 48, 27, 166, 77, 146, 158, 231, 83, 111, 229, 122, 60, 211, 133, \
			55, 46, 245, 40, 244, 102, 143, 54, 65, 25, 63, 161, 1, 216, 80, 73, \
			18, 169, 200, 196, 135, 130, 116, 188, 159, 86, 164, 100, 109, 198, 173, 186, \
			250, 124, 123, 5, 202, 38, 147, 118, 126, 255, 82, 85, 212, 207, 206, 59, \
			189, 28, 42, 223, 183, 170, 213, 119, 248, 152, 2, 44, 154, 163, 70, 221, \
			43, 172, 9, 129, 22, 39, 253, 19, 98, 108, 110, 79, 113, 224, 232, 178, \
			97, 228, 251, 34, 242, 193, 238, 210, 144, 12, 191, 179, 162, 241, 81, 51, \
			107, 49, 192, 214, 31, 181, 199, 106, 157, 184, 84, 204, 176, 115, 121, 50, \
			138, 236, 205, 93, 222, 114, 67, 29, 24, 72, 243, 141, 128, 195, 78, 66, \
			140, 36, 103, 30, 227, 47, 16, 58, 69, 17, 209, 76, 132, 187, 45, 127, \
			197, 62, 94, 252, 153, 101, 155, 167, 219, 182, 3, 64, 52, 217, 215, 61, \
			168, 68, 175, 74, 185, 112, 104, 218, 165, 246, 4, 150, 208, 254, 142, 71, \
			230, 220, 105, 92, 145, 235, 249, 14, 41, 239, 156, 180, 226, 89, 203, 117
		};
		t_noise	n2 = obj->noise;
		double	noise = 0.0;
		double	intensity = 1.5;
		int		i = -1;
		
		while (++i != n2.oct)
		{
			noise += ft_noise(hit * n2.freq, perm) * intensity;
			intensity *= n2.persis;
			n2.freq *= 2.0;
		}
		
		return (noise);
		// return(noise * ((1.0 - n2.persis) / (1.0 - intensity)));
		// return (fmod(noise * ((1 - n2.persis) / (1 - intensity)), 1.0));
	}


// static double		ft_interp(const double a, const double b, const double c)
// {
// 	const double	d = (1.0 - cos(c * PI)) / 2.0;

// 	return (a * (1.0 - d) + b * d);
// }

// static double		ft_noise(double2 coords, const int perm)
// {
// 	const double2	c2 = floor(coords);
// 	const int		v1 = perm[];
	
// 	return ()
// }

// static double		ft_perlin_noise(const __global t_object *obj, const double2 coords)
// {
// 	int		i = -1;
// 	t_noise	noise = obj->noise;
// 	double	n = 0.0;
// 	double	p = 1.0;
// 	const int	perm[256] = {
// 	151, 91, 90, 15, 131, 13, 201, 95, 96, 53, 194, 233, 7, 225, 99, 37,\
// 	8, 240, 21, 10, 23, 190, 6, 148, 247, 120, 234, 75, 0, 26, 160, 137, \
// 	35, 11, 32, 57, 177, 33, 88, 237, 149, 56, 87, 174, 20, 125, 136, 171, \
// 	134, 139, 48, 27, 166, 77, 146, 158, 231, 83, 111, 229, 122, 60, 211, 133, \
// 	55, 46, 245, 40, 244, 102, 143, 54, 65, 25, 63, 161, 1, 216, 80, 73, \
// 	18, 169, 200, 196, 135, 130, 116, 188, 159, 86, 164, 100, 109, 198, 173, 186, \
// 	250, 124, 123, 5, 202, 38, 147, 118, 126, 255, 82, 85, 212, 207, 206, 59, \
// 	189, 28, 42, 223, 183, 170, 213, 119, 248, 152, 2, 44, 154, 163, 70, 221, \
// 	43, 172, 9, 129, 22, 39, 253, 19, 98, 108, 110, 79, 113, 224, 232, 178, \
// 	97, 228, 251, 34, 242, 193, 238, 210, 144, 12, 191, 179, 162, 241, 81, 51, \
// 	107, 49, 192, 214, 31, 181, 199, 106, 157, 184, 84, 204, 176, 115, 121, 50, \
// 	138, 236, 205, 93, 222, 114, 67, 29, 24, 72, 243, 141, 128, 195, 78, 66, \
// 	140, 36, 103, 30, 227, 47, 16, 58, 69, 17, 209, 76, 132, 187, 45, 127, \
// 	197, 62, 94, 252, 153, 101, 155, 167, 219, 182, 3, 64, 52, 217, 215, 61, \
// 	168, 68, 175, 74, 185, 112, 104, 218, 165, 246, 4, 150, 208, 254, 142, 71, \
// 	230, 220, 105, 92, 145, 235, 249, 14, 41, 239, 156, 180, 226, 89, 203, 117
// 	};

// 	while (++i < noise.oct)
// 	{
// 		n += p * ft_noise(coords * noise.freq, perm);
// 		p *= noise.persis;
// 		noise.freq *= 2.0;
// 	}
// 	return (n * (1.0 - noise.persis) / (1.0 - p));
// }