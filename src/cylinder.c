/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olskor <olskor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 16:09:21 by olskor            #+#    #+#             */
/*   Updated: 2023/12/29 22:57:54 by olskor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_Vec3	get_uv_cyl(t_cylinder cylinder, t_Vec3 p);

typedef struct s_hcyl
{
	t_Vec3	oc;
	t_Vec3	abc;
	double	discriminant;
	double	temp;
	double	max2;
	t_Vec3	p;
	t_Vec3	norm;
}				t_hcyl;

t_hit	hit_cylinder2(t_hcyl hc, t_cylinder cylinder, t_hit hit)
{
	hc.norm = subvec3(subvec3(hc.p, cylinder.pos), scalevec3(cylinder.dir,
				dot(subvec3(hc.p, cylinder.pos), cylinder.dir)));
	hc.norm = scalevec3(hc.norm, 1 / cylinder.rad);
	hit.t = hc.temp;
	hit.p = hc.p;
	hit.norm = hc.norm;
	hit.uv = get_uv_cyl(cylinder, hit.p);
	hit.hit = 1;
	hit.mat = cylinder.mat;
	hit.t_max = hc.temp;
	return (hit);
}

t_hit	hit_cylinder1(t_cylinder c, t_Ray r, float t_min, float t_max)
{
	t_hit	hit;
	t_hcyl	hc;

	hc.oc = subvec3(r.orig, c.pos);
	hc.abc.x = vec3length2(r.dir) - pow(dot(r.dir, c.dir), 2);
	hc.abc.y = 2 * (dot(r.dir, hc.oc) - dot(r.dir, c.dir) * dot(hc.oc, c.dir));
	hc.abc.z = vec3length2(hc.oc) - pow(dot(hc.oc, c.dir), 2) - pow(c.rad, 2);
	hc.discriminant = pow(hc.abc.y, 2) - 4 * hc.abc.x * hc.abc.z;
	hit.hit = 0;
	hc.max2 = pow(c.h / 2, 2) + pow(c.rad, 2);
	if (hc.discriminant > 0)
	{
		hc.temp = (-hc.abc.y - sqrt(hc.discriminant)) / (2 * hc.abc.x);
		hc.p = vecat(r, hc.temp);
		if (hc.temp < t_max && hc.temp > t_min)
			if (vec3length2(subvec3(hc.p, c.pos)) < hc.max2)
				return (hit_cylinder2(hc, c, hit));
		hc.temp = (-hc.abc.y + sqrt(hc.discriminant)) / (2 * hc.abc.x);
		hc.p = vecat(r, hc.temp);
		if (hc.temp < t_max && hc.temp > t_min)
			if (vec3length2(subvec3(hc.p, c.pos)) < hc.max2)
				return (hit_cylinder2(hc, c, hit));
	}
	return (hit);
}

t_hit	hit_planedisk1(t_cylinder cylinder, t_Ray ray, float t_min, float t_max)
{
	t_hit	hit;
	t_hcyl	hc;

	hc.discriminant = dot(cylinder.dir, ray.dir);
	if (fabs(hc.discriminant) > 0.0001)
	{
		hc.temp = dot(subvec3(addvec3(cylinder.pos, scalevec3(cylinder.dir,
							-cylinder.h / 2)), ray.orig),
				cylinder.dir) / hc.discriminant;
		if (hc.temp > t_min && hc.temp < t_max)
		{
			hit.t = hc.temp;
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
	t_hcyl	hc;

	hc.discriminant = dot(cylinder.dir, ray.dir);
	if (fabs(hc.discriminant) > 0.0001)
	{
		hc.temp = dot(subvec3(addvec3(cylinder.pos, scalevec3(cylinder.dir,
							cylinder.h / 2)), ray.orig),
				cylinder.dir) / hc.discriminant;
		if (hc.temp > t_min && hc.temp < t_max)
		{
			hit.t = hc.temp;
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
			hit = hit_temp;
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
		cylinder++;
	}
	return (hit);
}
