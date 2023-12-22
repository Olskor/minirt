/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olskor <olskor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 15:31:16 by olskor            #+#    #+#             */
/*   Updated: 2023/12/22 18:28:15 by olskor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_hit	hit_sphere2(double temp, t_sphere sphere, t_Ray ray, int didhit)
{
	t_hit	hit;

	if (!didhit)
	{
		hit.hit = 0;
		return (hit);
	}
	hit.t = temp;
	hit.p = vecat(ray, hit.t);
	hit.norm = scalevec3(subvec3(hit.p, sphere.pos), 1 / sphere.rad);
	hit.mat = sphere.mat;
	hit.hit = 1;
	return (hit);
}

t_hit	hit_sphere1(t_sphere sphere, t_Ray ray, float t_min, float t_max)
{
	t_Vec3	oc;
	t_Vec3	abc;
	double	discriminant;
	double	temp;

	oc = subvec3(ray.orig, sphere.pos);
	abc.x = vec3length2(ray.dir);
	abc.y = dot(oc, ray.dir);
	abc.z = vec3length2(oc) - pow(sphere.rad, 2);
	discriminant = pow(abc.y, 2) - abc.x * abc.z;
	if (discriminant > 0)
	{
		temp = (-abc.y - sqrt(discriminant)) / abc.x;
		if (temp < t_max && temp > t_min)
			return (hit_sphere2(temp, sphere, ray, 1));
		temp = (-abc.y + sqrt(discriminant)) / abc.x;
		if (temp < t_max && temp > t_min)
			return (hit_sphere2(temp, sphere, ray, 1));
	}
	return (hit_sphere2(0, sphere, ray, 0));
}

t_hit	hit_sphere(t_data *data, t_Ray ray, t_hit hit)
{
	int		i;
	t_hit	hit_temp;

	i = 0;
	while (i < data->spherenbr)
	{
		hit_temp = hit_sphere1(data->sphere[i], ray, 0.001, hit.t_max);
		if (hit_temp.hit)
		{
			hit.t_max = hit_temp.t;
			hit.norm = hit_temp.norm;
			hit.p = hit_temp.p;
			hit.t = hit_temp.t;
			hit.mat = hit_temp.mat;
			hit.hit = 1;
		}
		i++;
	}
	return (hit);
}
