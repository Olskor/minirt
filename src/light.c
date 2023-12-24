/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olskor <olskor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 04:40:26 by olskor            #+#    #+#             */
/*   Updated: 2023/12/24 21:48:28 by olskor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_hit	hit_light2(double temp, t_light light, t_Ray ray, int didhit)
{
	t_hit	hit;

	if (!didhit)
	{
		hit.hit = 0;
		return (hit);
	}
	hit.t = temp;
	hit.p = vecat(ray, hit.t);
	hit.norm = scalevec3(subvec3(hit.p, light.pos), 1 / 0.05);
	hit.mat.col = scalecol(light.col, light.intensity);
	hit.mat.col.t = 1;
	hit.mat.smooth = 0;
	hit.mat.metal = 0;
	hit.mat.refr = 0;
	hit.hit = 1;
	return (hit);
}

t_hit	hit_light1(t_light light, t_Ray ray, float t_min, float t_max)
{
	t_Vec3	oc;
	t_Vec3	abc;
	t_hit	hit;
	double	discriminant;
	double	temp;

	oc = subvec3(ray.orig, light.pos);
	abc.x = vec3length2(ray.dir);
	abc.y = dot(oc, ray.dir);
	abc.z = vec3length2(oc) - pow(0.05, 2);
	discriminant = pow(abc.y, 2) - abc.x * abc.z;
	if (discriminant > 0)
	{
		temp = (-abc.y - sqrt(discriminant)) / abc.x;
		if (temp < t_max && temp > t_min)
			return (hit_light2(temp, light, ray, 1));
		temp = (-abc.y + sqrt(discriminant)) / abc.x;
		if (temp < t_max && temp > t_min)
			return (hit_light2(temp, light, ray, 1));
	}
	return (hit_light2(0, light, ray, 0));
}

t_hit	hit_light(t_data *data, t_Ray ray, t_hit hit)
{
	int		i;
	t_hit	hit_temp;

	i = 0;
	while (i < data->lightnbr)
	{
		hit_temp = hit_light1(data->light[i], ray, 0.001, hit.t_max);
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
