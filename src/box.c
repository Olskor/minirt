/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   box.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olskor <olskor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 16:09:21 by olskor            #+#    #+#             */
/*   Updated: 2023/12/29 12:39:30 by olskor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_Vec3	get_box_uv(t_Vec3 p, t_box box)
{
	t_Vec3	uv;
	t_Vec3	n;

	n = unit_vec3(subvec3(p, box.min));
	uv.x = 0.5 + atan2(n.z, n.x) / (2 * M_PI);
	uv.y = 0.5 - asin(n.y) / M_PI;
	return (uv);
}

t_Vec3	box_normals(t_Vec3 p, t_box box)
{
	t_Vec3	normals;

	normals = vec3(0, 0, 0);
	if (p.x <= box.min.x + 0.0001)
		normals.x = -1;
	else if (p.x >= box.max.x - 0.0001)
		normals.x = 1;

	if (p.y <= box.min.y + 0.0001)
		normals.y = -1;
	else if (p.y >= box.max.y - 0.0001)
		normals.y = 1;

	if (p.z <= box.min.z + 0.0001)
		normals.z = -1;
	else if (p.z >= box.max.z - 0.0001)
		normals.z = 1;

	return (normals);
}

t_hit	hit_box1(t_box box, t_Ray ray, float t_min, float t_max)
{
	t_hit	hit;
	t_Vec3	invdir;
	t_Vec3	tbot;
	t_Vec3	ttop;
	t_Vec3	tmin;
	t_Vec3	tmax;

	hit.hit = 0;
	invdir = vec3(1 / ray.dir.x, 1 / ray.dir.y, 1 / ray.dir.z);
	tbot = mulvec3(invdir, subvec3(box.min, ray.orig));
	ttop = mulvec3(invdir, subvec3(box.max, ray.orig));
	tmin = vec3(min(ttop.x, tbot.x), min(ttop.y, tbot.y), min(ttop.z, tbot.z));
	tmax = vec3(max(ttop.x, tbot.x), max(ttop.y, tbot.y), max(ttop.z, tbot.z));
	t_min = max(t_min, max(tmin.x, max(tmin.y, tmin.z)));
	t_max = min(t_max, min(tmax.x, min(tmax.y, tmax.z)));
	if (t_max < t_min)
		return (hit);
	hit.t = t_min;
	hit.p = vecat(ray, t_min);
	hit.norm = box_normals(hit.p, box);
	hit.hit = 1;
	hit.mat = box.mat;
	hit.uv = get_box_uv(hit.p, box);
	return (hit);
}

t_hit	hit_box(t_data *data, t_Ray ray, t_hit hit)
{
	t_box	**box;
	t_hit	hit_temp;

	box = data->box;
	while (box && *box)
	{
		hit_temp = hit_box1(**box, ray, 0.001, hit.t_max);
		if (hit_temp.hit)
		{
			hit = hit_temp;
			hit.t_max = hit_temp.t;
			hit.obj = 3;
		}
		box++;
	}
	return (hit);
}
