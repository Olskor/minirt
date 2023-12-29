/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olskor <olskor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 16:09:21 by olskor            #+#    #+#             */
/*   Updated: 2023/12/29 12:31:22 by olskor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_Vec3	get_uv_cyl(t_cylinder cylinder, t_Vec3 p)
{
	t_Vec3	uv;
	t_Vec3	n;

	n = unit_vec3(subvec3(p, cylinder.pos));
	uv.x = 0.5 + atan2(n.z, n.x) / (2 * M_PI);
	uv.y = 0.5 - asin(n.y) / M_PI;
	return (uv);
}

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
			if (vec3length2(subvec3(p, cylinder.pos)) < max2)
			{
				norm = subvec3(subvec3(p, cylinder.pos), scalevec3(cylinder.dir, dot(subvec3(p, cylinder.pos), cylinder.dir)));
				norm = scalevec3(norm, 1 / cylinder.rad);
				hit.t = temp;
				hit.p = p;
				hit.norm = norm;
				hit.uv = get_uv_cyl(cylinder, hit.p);
				hit.hit = 1;
				hit.mat = cylinder.mat;
				return (hit);
			}
		}
		temp = (-abc.y + sqrt(discriminant)) / (2 * abc.x);
		if (temp < t_max && temp > t_min)
		{
			p = vecat(ray, temp);
			if (vec3length2(subvec3(p, cylinder.pos)) < max2)
			{
				norm = subvec3(subvec3(p, cylinder.pos), scalevec3(cylinder.dir, dot(subvec3(p, cylinder.pos), cylinder.dir)));
				norm = scalevec3(norm, 1 / cylinder.rad);
				hit.t = temp;
				hit.p = p;
				hit.norm = norm;
				hit.uv = get_uv_cyl(cylinder, hit.p);
				hit.hit = 1;
				hit.mat = cylinder.mat;
				return (hit);
			}
		}
	}
	hit.hit = 0;
	return (hit);
}

t_hit	hit_planedisk1(t_cylinder cylinder, t_Ray ray, float t_min, float t_max)
{
	t_hit	hit;
	float	discriminant;
	float	temp;

	discriminant = dot(cylinder.dir, ray.dir);
	if (fabs(discriminant) > 0.0001)
	{
		temp = dot(subvec3(addvec3(cylinder.pos, scalevec3(cylinder.dir,
							-cylinder.h / 2)), ray.orig),
				cylinder.dir) / discriminant;
		if (temp > t_min && temp < t_max)
		{
			hit.t = temp;
			hit.p = vecat(ray, hit.t);
			hit.norm = scalevec3(cylinder.dir, -1);
			hit.uv = get_uv_cyl(cylinder, hit.p);
			hit.hit = 1;
			hit.mat = cylinder.mat;
			if (vec3length2(subvec3(hit.p, addvec3(cylinder.pos,
							scalevec3(cylinder.dir, -cylinder.h
								/ 2)))) < cylinder.rad * cylinder.rad)
				return (hit);
		}
	}
	hit.hit = 0;
	return (hit);
}

t_hit	hit_planedisk2(t_cylinder cylinder, t_Ray ray, float t_min, float t_max)
{
	t_hit	hit;
	float	discriminant;
	float	temp;

	discriminant = dot(cylinder.dir, ray.dir);
	if (fabs(discriminant) > 0.0001)
	{
		temp = dot(subvec3(addvec3(cylinder.pos, scalevec3(cylinder.dir,
							cylinder.h / 2)), ray.orig),
				cylinder.dir) / discriminant;
		if (temp > t_min && temp < t_max)
		{
			hit.t = temp;
			hit.p = vecat(ray, hit.t);
			hit.norm = cylinder.dir;
			hit.uv = get_uv_cyl(cylinder, hit.p);
			hit.hit = 1;
			hit.mat = cylinder.mat;
			if (vec3length2(subvec3(hit.p, addvec3(cylinder.pos,
							scalevec3(cylinder.dir, cylinder.h
								/ 2)))) < cylinder.rad * cylinder.rad)
				return (hit);
		}
	}
	hit.hit = 0;
	return (hit);
}

t_hit	hit_cylinder(t_data *data, t_Ray ray, t_hit hit)
{
	t_cylinder	**cylinder;
	t_hit		hit_temp;

	cylinder = data->cylinder;
	while (cylinder && *cylinder)
	{
		hit_temp = hit_cylinder1(**cylinder, ray, 0.001, hit.t_max);
		if (hit_temp.hit)
		{
			hit = hit_temp;
			hit.t_max = hit_temp.t;
		}
		hit_temp = hit_planedisk1(**cylinder, ray, 0.001, hit.t_max);
		if (hit_temp.hit)
		{
			hit = hit_temp;
			hit.t_max = hit_temp.t;
		}
		hit_temp = hit_planedisk2(**cylinder, ray, 0.001, hit.t_max);
		if (hit_temp.hit)
		{
			hit = hit_temp;
			hit.t_max = hit_temp.t;
		}
		if (hit_temp.hit)
			hit.obj = 2;
		cylinder++;
	}
	return (hit);
}
