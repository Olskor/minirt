/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olskor <olskor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 16:03:50 by olskor            #+#    #+#             */
/*   Updated: 2023/12/28 16:42:30 by olskor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_hit	hit_tri2(t_Vec4 afuv, t_Vec3 edge1, t_Vec3 edge2, t_Ray ray)
{
	t_hit	hit;

	hit.hit = 0;
	if (afuv.w > 0.00001 && afuv.w < afuv.x)
	{
		hit.t = afuv.w;
		hit.p = vecat(ray, afuv.w);
		hit.norm = unit_vec3(cross(edge1, edge2));
		hit.hit = 1;
		return (hit);
	}
	return (hit);
}

int	hit_box_tri(t_box_tri box, t_Ray ray, float t_min, float t_max)
{
	t_Vec3	invdir;
	t_Vec3	tbot;
	t_Vec3	ttop;
	t_Vec3	tmin;
	t_Vec3	tmax;

	invdir = vec3(1 / ray.dir.x, 1 / ray.dir.y, 1 / ray.dir.z);
	tbot = mulvec3(invdir, subvec3(box.min, ray.orig));
	ttop = mulvec3(invdir, subvec3(box.max, ray.orig));
	tmin = vec3(min(ttop.x, tbot.x), min(ttop.y, tbot.y), min(ttop.z, tbot.z));
	tmax = vec3(max(ttop.x, tbot.x), max(ttop.y, tbot.y), max(ttop.z, tbot.z));
	t_min = max(t_min, max(tmin.x, max(tmin.y, tmin.z)));
	t_max = min(t_max, min(tmax.x, min(tmax.y, tmax.z)));
	if (t_max < t_min)
		return (0);
	return (1);
}

t_hit	hit_tri1(t_Tri triangle, t_Ray ray, float t_min, float t_max)
{
	t_hit	hit;
	t_Vec3	edge1;
	t_Vec3	edge2;
	t_Tri	hsq;
	t_Vec4	afuv;

	edge1 = subvec3(triangle.pos2, triangle.pos1);
	edge2 = subvec3(triangle.pos3, triangle.pos1);
	hit.hit = 0;
	hsq.pos1 = cross(ray.dir, edge2);
	afuv.w = dot(edge1, hsq.pos1);
	if (afuv.w > -0.00001 && afuv.w < 0.00001)
		return (hit);
	afuv.x = 1 / afuv.w;
	hsq.pos2 = subvec3(ray.orig, triangle.pos1);
	afuv.y = afuv.x * dot(hsq.pos2, hsq.pos1);
	if (afuv.y < 0.0 || afuv.y > 1.0)
		return (hit);
	hsq.pos3 = cross(hsq.pos2, edge1);
	afuv.z = afuv.x * dot(ray.dir, hsq.pos3);
	if (afuv.z < 0.0 || afuv.y + afuv.z > 1.0)
		return (hit);
	afuv.w = afuv.x * dot(edge2, hsq.pos3);
	afuv.x = t_max;
	return (hit_tri2(afuv, edge1, edge2, ray));
}

t_hit	hit_mesh1(t_mesh mesh, t_Ray ray, t_hit hit)
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

t_hit	hit_mesh(t_data *data, t_Ray ray, t_hit hit)
{
	int		i;

	i = 0;
	while (i < data->meshnbr)
	{
		if (hit_box_tri(data->mesh[i].box, ray, 0.001, hit.t_max))
			hit = hit_mesh1(data->mesh[i], ray, hit);
		i++;
	}
	return (hit);
}
