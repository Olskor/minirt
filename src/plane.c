/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olskor <olskor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 16:03:50 by olskor            #+#    #+#             */
/*   Updated: 2023/12/21 16:09:09 by olskor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_hit	hit_plane1(t_plane plane, t_Ray ray, float t_min, float t_max)
{
	t_hit	hit;
	float	denom;
	float	t;

	denom = dot(plane.norm, ray.dir);
	if (fabs(denom) > 0.0001)
	{
		t = dot(subvec3(plane.pos, ray.orig), plane.norm) / denom;
		if (t > t_min && t < t_max)
		{
			hit.t = t;
			hit.p = vecat(ray, hit.t);
			hit.norm = plane.norm;
			hit.hit = 1;
			hit.mat = plane.mat;
			return (hit);
		}
	}
	hit.hit = 0;
	return (hit);
}

t_hit	hit_plane(t_data *data, t_Ray ray, t_hit hit)
{
	int		i;
	t_hit	hit_temp;

	i = 0;
	while (i < data->planenbr)
	{
		hit_temp = hit_plane1(data->plane[i], ray, 0.001, hit.t_max);
		if (hit_temp.hit)
		{
			hit.t_max = hit_temp.t;
			hit.norm = hit_temp.norm;
			hit.p = hit_temp.p;
			hit.t = hit_temp.t;
			hit.mat = hit_temp.mat;
			hit.hit = hit_temp.hit;
		}
		i++;
	}
	return (hit);
}