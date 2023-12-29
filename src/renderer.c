/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olskor <olskor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 01:13:30 by olskor            #+#    #+#             */
/*   Updated: 2023/12/29 12:33:39 by olskor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "libft.h"

int	loop(t_data *data)
{
	double	theta;
	double	h;

	data->cam.focal = vec3length(subvec3(data->cam.pos, data->cam.rot));
	theta = data->cam.fov * 3.1415 / 180;
	h = tan(theta / 2);
	data->cam.vhe = 2.0 * h * data->cam.focal;
	data->cam.vwi = data->cam.aspect * data->cam.vhe;

	data->cam.w = unit_vec3(subvec3(data->cam.pos, data->cam.rot));
	data->cam.u = unit_vec3(cross(data->cam.vup, data->cam.w));
	data->cam.v = cross(data->cam.w, data->cam.u);

	data->cam.v_u = scalevec3(data->cam.u, data->cam.vwi);
	data->cam.v_v = scalevec3(data->cam.v, -data->cam.vhe);
	data->cam.pixdu = scalevec3(data->cam.v_u, 1 / (float) data->wi);
	data->cam.pixdv = scalevec3(data->cam.v_v, 1 / (float) data->he);
	data->cam.v_ul = subvec3(data->cam.pos, subvec3(scalevec3(data->cam.w,
					data->cam.focal), subvec3(scalevec3(data->cam.v_u, -0.5),
					scalevec3(data->cam.v_v, 0.5))));
	data->cam.pix00 = data->cam.v_ul;

	render(data);
	return (0);
}

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

t_Col	pb_shading(t_Ray ray, t_data *data, t_hit hit, int depth)
{
	t_Vec3	target;
	t_Vec3	diffuse;
	t_Vec3	specular;
	t_Col	col;
	int		isspecular;

	if (hit.hit)
	{
		if (hit.mat.col.t > 0)
			return (scalecol(hit.mat.col, 1));
		diffuse = lambertian_random_ray(hit.norm, data);
		specular = reflect(ray.dir, hit.norm);
		target = lerpvec3(diffuse, specular, hit.mat.smooth);
		col = mulcol(scalecol(raycol(newray(hit.p, target),
						data, depth - 1), 0.5),
				lerpcol(col4(0, 0.4, 0.4, 0.4), hit.mat.col, hit.mat.metal));
		col = scalecol(col, saturate(hit.mat.smooth + hit.mat.metal));
		col = addcol(col,
				mulcol(scalecol(raycol(newray(hit.p, diffuse),
							data, depth - 1), 0.5), hit.mat.col));
		return (col);
	}
	return (col4(0, 0, 0, 0));
}

t_Col	cook_torrance(t_hit hit, t_Ray ray, t_light light, t_Col lightcol);

t_Col	light_ray(t_Ray ray, t_data *data, t_hit hit, t_light light)
{
	t_Col	col;
	t_Col	lightcol;
	t_Vec3	lightdir;
	float	ndoth;
	float	intensity;

	col = col4(0, 0, 0, 0);
	lightdir = subvec3(light.pos, hit.p);
	ndoth = dot(hit.norm, unit_vec3(addvec3(lightdir,
					subvec3(ray.orig, hit.p))));
	intensity = light.intensity / vec3length2(lightdir);
	intensity *= (1 - hit.mat.metal);
	lightcol = raycol(newray(hit.p, lightdir), data, -1);
	col = mulcol(hit.mat.col, scalecol(lightcol, saturate(dot(hit.norm, lightdir)) * intensity / 5));
	col = addcol(col, cook_torrance(hit, ray, light, lightcol));
	return (col);
}

t_Col	simple_shading(t_Ray ray, t_data *data, t_hit hit, int depth)
{
	t_Col	col;
	float	intensity;
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

t_Col	raycol(t_Ray ray, t_data *data, int depth)
{
	t_hit	hit;

	if (depth == 0)
		return (scalecol(data->ambient, 2));
	hit.t_max = 100;
	hit.hit = 0;
	hit.obj = 0;
	hit = hit_sphere(data, ray, hit);
	hit = hit_plane(data, ray, hit);
	hit = hit_cylinder(data, ray, hit);
	hit = hit_mesh(data, ray, hit);
	hit = hit_box(data, ray, hit);
	if (depth == -1)
		hit = hit_light(data, ray, hit);
	if (hit.mat.tex && hit.hit && depth >= 0)
		hit.mat.col = mulcol(hit.mat.col, get_texcol(hit.mat.tex, hit.uv));
	if (hit.mat.bump && hit.hit && depth >= 0)
		hit.norm = bump(hit.norm, hit.mat.bump, hit.uv);
	if (hit.mat.pbr && hit.hit && depth >= 0)
	{
		hit.mat.smooth = get_texcol(hit.mat.pbr, hit.uv).g * hit.mat.smooth;
		hit.mat.metal = get_texcol(hit.mat.pbr, hit.uv).r * hit.mat.metal;
	}
	if (depth == -1)
		return (simple_shading(ray, data, hit, depth));
	return (addcol(pb_shading(ray, data, hit, depth), simple_shading(ray, data, hit, depth)));
}

int	render(t_data *data)
{
	t_Int2	s;
	t_Ray	ray;
	t_Col	col;
	t_Vec3	pixpos;
	float	weight;

	s = int2(0, 0);
	render_background(&data->img, 0);
	while (s.y < data->he)
	{
		while (s.x < data->wi)
		{
			pixpos = addvec3(data->cam.pix00, addvec3(scalevec3(data->cam.pixdu, s.x),scalevec3(data->cam.pixdv, s.y)));
			ray.dir = (subvec3(addvec3(pixpos, scalevec3(random_in_unit_sphere(data), 0.5 * vec3length(data->cam.pixdu))), data->cam.pos));
			ray.orig = data->cam.pos;
			weight = 1.0 / ((float) data->sample + 1);
			if (data->sample == 0)
				data->cimg[s.y][s.x] = addcol(col4(0, 0, 0, 0), raycol(ray, data, 1 + data->bounces));
			else
				data->cimg[s.y][s.x] = addcol(scalecol(data->cimg[s.y][s.x], 1 - weight), scalecol(raycol(ray, data, 1 + data->bounces), weight));
			img_pix_put(&data->img, s.x++, s.y, create_trgb(data->cimg[s.y][s.x]));
		}
		s = int2(0, s.y + 1);
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img.mlx_img, 0, 0);
	if (data->sample >= MAX_SAMPLES)
	{
		data->sample = 0;
		data->cam.pos = vec3(data->cam.pos.x + 0.1, data->cam.pos.y, data->cam.pos.z);
		save_img(data);
		return (0);
	}
	if (data->frame >= MAX_FRAMES)
	{
		close_window(data);
		return (0);
	}
	printf("sample : %d, %f\n", data->sample, data->cimg[0][0].b);
	data->sample++;
	return (0);
}

