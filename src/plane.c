/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olskor <olskor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 16:03:50 by olskor            #+#    #+#             */
/*   Updated: 2023/12/29 12:31:14 by olskor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_Vec3	computeprimarytexdir(t_Vec3 normal)
{
	t_Vec3	a;
	t_Vec3	b;
	t_Vec3	c;
	t_Vec3	max_ab;

	a = cross(normal, vec3(1, 0, 0));
	b = cross(normal, vec3(0, 1, 0));
	if (dot(a, a) < dot(b, b))
		max_ab = b;
	else
		max_ab = a;
	c = cross(normal, vec3(0, 0, 1));
	if (dot(max_ab, max_ab) < dot(c, c))
		return (unit_vec3(c));
	else
		return (unit_vec3(max_ab));
}

t_Vec3	get_plane_uv(t_plane plane, t_Vec3 p)
{
	t_Vec3	local_p;
	t_Vec3	u_axis;
	t_Vec3	v_axis;
	t_Vec3	uv;

	local_p = p;
	u_axis = computeprimarytexdir(unit_vec3(plane.norm));
	v_axis = cross(unit_vec3(plane.norm), u_axis);
	uv.x = dot(local_p, u_axis);
	uv.y = dot(local_p, v_axis);
	uv.z = 0;
	uv.x = (modf(uv.x, &uv.x));
	if (uv.x < 0)
		uv.x += 1;
	uv.y = (modf(uv.y, &uv.y));
	if (uv.y < 0)
		uv.y += 1;
	return (uv);
}

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
			hit.uv = get_plane_uv(plane, hit.p);
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
	t_plane	**plane;
	t_hit	hit_temp;

	plane = data->plane;
	while (plane && *plane)
	{
		hit_temp = hit_plane1(**plane, ray, 0.001, hit.t_max);
		if (hit_temp.hit)
		{
			hit.t_max = hit_temp.t;
			hit.norm = hit_temp.norm;
			hit.p = hit_temp.p;
			hit.t = hit_temp.t;
			hit.mat = hit_temp.mat;
			hit.uv = hit_temp.uv;
			hit.hit = hit_temp.hit;
			hit.obj = 1;
		}
		plane++;
	}
	return (hit);
}
