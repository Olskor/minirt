/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olskor <olskor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 16:03:50 by olskor            #+#    #+#             */
/*   Updated: 2023/12/23 01:09:06 by olskor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_hit	hit_tri1(t_Tri triangle, t_Ray ray, float t_min, float t_max)
{
	t_hit	hit;
	t_Vec3	edge1;
	t_Vec3	edge2;
	t_Vec3	h;
	t_Vec3	s;
	t_Vec3	q;
	float	a;
	float	f;
	float	u;
	float	v;

	edge1 = subvec3(triangle.pos2, triangle.pos1);
	edge2 = subvec3(triangle.pos3, triangle.pos1);
	hit.hit = 0;
	h = cross(ray.dir, edge2);
	a = dot(edge1, h);
	if (a > -0.00001 && a < 0.00001)
		return (hit);
	f = 1 / a;
	s = subvec3(ray.orig, triangle.pos1);
	u = f * dot(s, h);
	if (u < 0.0 || u > 1.0)
		return (hit);
	q = cross(s, edge1);
	v = f * dot(ray.dir, q);
	if (v < 0.0 || u + v > 1.0)
		return (hit);
	float t = f * dot(edge2, q);
	if (t > 0.00001 && t < t_max)
	{
		hit.t = t;
		hit.p = vecat(ray, t);
		hit.norm = unit_vec3(cross(edge1, edge2));
		hit.hit = 1;
		return (hit);
	}
	return (hit);
}

t_hit	hit_mesh(t_mesh mesh, t_Ray ray, t_hit hit)
{
	int		i;
	t_hit	hit_temp;

	i = 0;
	while (i < mesh.trinbr)
	{
		hit_temp = hit_tri1(mesh.tri[i], ray, 0.001, hit.t_max);
		if (hit_temp.hit)
		{
			hit.t_max = hit_temp.t;
			hit.norm = hit_temp.norm;
			hit.p = hit_temp.p;
			hit.t = hit_temp.t;
			hit.mat = mesh.mat;
			hit.hit = hit_temp.hit;
		}
		i++;
	}
	return (hit);
}
