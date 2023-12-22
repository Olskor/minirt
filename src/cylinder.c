/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olskor <olskor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 16:09:21 by olskor            #+#    #+#             */
/*   Updated: 2023/12/22 16:46:18 by olskor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_hit hit_cylinder1(t_cylinder cylinder, t_Ray ray, float t_min, float t_max)
{
	t_hit	hit;
	t_Vec3	oc;
	t_Vec3	abc;
	double	discriminant;
	double	temp;
	double	max2;
	t_Vec3	p;
	t_Vec3	norm;

	oc = subvec3(ray.orig, cylinder.pos);
	abc.x = vec3length2(ray.dir) - pow(dot(ray.dir, cylinder.dir), 2);
	abc.y = 2 * (dot(ray.dir, oc) - dot(ray.dir, cylinder.dir) * dot(oc, cylinder.dir));
	abc.z = vec3length2(oc) - pow(dot(oc, cylinder.dir), 2) - pow(cylinder.rad, 2);
	discriminant = pow(abc.y, 2) - 4 * abc.x * abc.z;
	hit.hit = 0;
	max2 = pow(cylinder.h / 2, 2) + pow(cylinder.rad, 2);
	if (discriminant > 0)
	{
		temp = (-abc.y - sqrt(discriminant)) / (2 * abc.x);
		if (temp < t_max && temp > t_min)
		{
			p = vecat(ray, temp);
			if (vec3length2(subvec3(p, cylinder.pos)) > max2)
				return (hit);
			norm = subvec3(subvec3(p, cylinder.pos), scalevec3(cylinder.dir, dot(subvec3(p, cylinder.pos), cylinder.dir)));
			norm = scalevec3(norm, 1 / cylinder.rad);
			hit.t = temp;
			hit.p = p;
			hit.norm = norm;
			hit.hit = 1;
			hit.mat = cylinder.mat;
			return (hit);
		}
		temp = (-abc.y + sqrt(discriminant)) / (2 * abc.x);
		if (temp < t_max && temp > t_min)
		{
			p = vecat(ray, temp);
			if (vec3length2(subvec3(p, cylinder.pos)) > max2)
				return (hit);
			norm = subvec3(subvec3(p, cylinder.pos), scalevec3(cylinder.dir, dot(subvec3(p, cylinder.pos), cylinder.dir)));
			norm = scalevec3(norm, 1 / cylinder.rad);
			hit.t = temp;
			hit.p = p;
			hit.norm = norm;
			hit.hit = 1;
			hit.mat = cylinder.mat;
			return (hit);
		}
	}
	hit.hit = 0;
	return (hit);
}

t_hit	hit_cylinder(t_data *data, t_Ray ray, t_hit hit)
{
	int		i;
	t_hit	hit_temp;

	i = 0;
	while (i < data->cylindernbr)
	{
		hit_temp = hit_cylinder1(data->cylinder[i], ray, 0.001, hit.t_max);
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
