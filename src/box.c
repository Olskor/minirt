/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   box.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olskor <olskor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 16:09:21 by olskor            #+#    #+#             */
/*   Updated: 2024/01/11 12:33:08 by olskor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_Vec3 get_box_uv(t_Vec3 p, t_box box)
{
	t_Vec3 uv;
	t_Vec3 n;

	n = unit_vec3(subvec3(p, box.min));
	uv.x = 0.5 + atan2(n.z, n.x) / (2 * M_PI);
	uv.y = 0.5 - asin(n.y) / M_PI;
	return (uv);
}

t_Vec3 box_normals(t_Vec3 p, t_box box)
{
	t_Vec3 normals;

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

t_hit hit_box1(t_box box, t_Ray ray, float t_min, float t_max)
{
	t_hit hit;
	t_Vec3 invdir;
	t_Vec3 tbot;
	t_Tri t;

	hit.hit = 0;
	invdir = vec3(1 / ray.dir.x, 1 / ray.dir.y, 1 / ray.dir.z);
	tbot = mulvec3(invdir, subvec3(box.min, ray.orig));
	t.pos1 = mulvec3(invdir, subvec3(box.max, ray.orig));
	t.pos2 = vec3(min(t.pos1.x, tbot.x),
				  min(t.pos1.y, tbot.y), min(t.pos1.z, tbot.z));
	t.pos3 = vec3(max(t.pos1.x, tbot.x),
				  max(t.pos1.y, tbot.y), max(t.pos1.z, tbot.z));
	t_min = max(t_min, max(t.pos2.x, max(t.pos2.y, t.pos2.z)));
	t_max = min(t_max, min(t.pos3.x, min(t.pos3.y, t.pos3.z)));
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

t_hit hit_box(t_data *data, t_Ray ray, t_hit hit)
{
	t_box **box;
	t_hit hit_temp;

	box = 0;
	if (data)
		box = 0;
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

void	create_cube(t_data *data)
{
	t_cube	**cube;
	int		i;

	cube = data->cube;
	i = 0;
	while (cube && *cube)
		cube = cube + 1 + (i++ *0);
	if (i == 0)
		return ;
	data->mesh = (t_mesh **)malloc(sizeof(t_mesh *) * (i + 1));
	cube = data->cube;
	i = 0;
	while (cube && *cube)
	{
		data->mesh[i] = (t_mesh *)malloc(sizeof(t_mesh));
		*data->mesh[i] = read_obj("box.obj");
		data->mesh[i]->pos = (*cube)->pos;
		data->mesh[i]->mat = (*cube)->mat;
		data->mesh[i]->dir = unit_vec3(vec3((*cube)->dir.x, (*cube)->dir.y, (*cube)->dir.z));
		data->mesh[i]->up = unit_vec3(cross(data->mesh[i]->dir, vec3(0, 1, 0)));
		data->mesh[i]->scale = vec3((*cube)->size, (*cube)->size, (*cube)->size);
		*data->mesh[i] = rotate_mesh(*data->mesh[0]);
		*data->mesh[i] = scale_mesh(*data->mesh[0]);
		*data->mesh[i] = translate_mesh(*data->mesh[0]);
		data->mesh[i]->box = calculate_box(*data->mesh[0]);
		cube = cube + 1 + (i++ *0);
	}
	data->mesh[i] = 0;
}
