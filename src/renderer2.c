/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olskor <olskor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 23:35:03 by olskor            #+#    #+#             */
/*   Updated: 2023/12/29 23:57:38 by olskor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_Col	cook_torrance(t_hit hit, t_Ray ray, t_light light, t_Col lightcol);

t_Col	computesky(t_Vec3 dir, t_sky sky)
{
	float	grad;
	t_Col	col;
	float	strengh;

	strengh = 2;
	grad = 0.5 * (dir.y + 1.0);
	grad = (1.0 - grad) * 0 + grad * strengh;
	if (dir.y > 0)
	{
		col = col4(0, strengh - (grad * 4 / 5), strengh
				- (grad * 6 / 10), strengh - 0.1);
		if (-dot(unit_vec3(sky.sun), unit_vec3(dir)) > 0.995)
			col = addcol(col, col4(1, sky.intensity * 100,
						sky.intensity * 100, sky.intensity * 80));
	}
	if (dir.y <= 0)
		col = col4(0, 0.5, 0.5, 0.5);
	return (col);
}

t_Col	light_ray(t_Ray ray, t_data *data, t_hit hit, t_light light)
{
	t_Col	col;
	t_Col	lightcol;
	t_Vec3	lightdir;
	float	intensity;

	col = col4(0, 0, 0, 0);
	lightdir = subvec3(light.pos, hit.p);
	intensity = light.intensity / vec3length2(lightdir);
	intensity *= (1 - hit.mat.metal);
	lightcol = raycol(newray(hit.p, lightdir), data, -1);
	col = mulcol(hit.mat.col, scalecol(lightcol,
				saturate(dot(hit.norm, lightdir)) * intensity / 5));
	col = addcol(col, cook_torrance(hit, ray, light, lightcol));
	return (col);
}

t_Col	simple_shading(t_Ray ray, t_data *data, t_hit hit, int depth)
{
	t_Col	col;
	t_light	**light;

	if (hit.hit)
	{
		if (depth == -1)
		{
			if (hit.mat.col.t > 0)
				return (scalecol(hit.mat.col, 1));
			return (data->ambient);
		}
		col = col4(0, 0, 0, 0);
		light = data->light;
		while (light && *light)
		{
			col = addcol(col, light_ray(ray, data, hit, **light));
			light++;
		}
		return (mulcol(col, hit.mat.col));
	}
	if (data->sky.active)
		return (computesky(unit_vec3(ray.dir), data->sky));
	if (depth < 1 + data->bounces)
		return (scalecol(data->ambient, 2));
	return (col4(0, 0, 0, 0));
}

t_Vec3	unpack_normal(t_Col col)
{
	t_Vec3	norm;

	norm.x = -(col.g * 2 - 1);
	norm.y = -(col.r * 2 - 1);
	norm.z = col.b;
	return (norm);
}

t_Vec3	bump(t_Vec3 normal, t_Tex *bump, t_Vec3 uv)
{
	t_Col	col;
	t_Vec3	bumpnorm;
	t_Vec3	tangent;
	t_Vec3	binormal;
	t_Vec3	newnorm;

	col = get_texcol(bump, uv);
	bumpnorm = unpack_normal(col);
	tangent = cross(normal, vec3(0, 1, 0));
	if (vec3length2(tangent) < 0.001)
		tangent = cross(normal, vec3(1, 0, 0));
	binormal = cross(normal, tangent);
	newnorm = addvec3(scalevec3(tangent, bumpnorm.x),
			addvec3(scalevec3(binormal, bumpnorm.y),
				scalevec3(normal, bumpnorm.z)));
	return (unit_vec3(newnorm));
}
