/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olskor <olskor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 01:13:30 by olskor            #+#    #+#             */
/*   Updated: 2023/11/28 14:58:09 by olskor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "libft.h"

int	loop(t_data *data)
{
	data->cam.vhe = 2.0;
	data->cam.vwi = data->cam.aspect * data->cam.vhe;
	data->cam.focal = 1.0;

	render(data);
	return (0);
}

void	img_pix_put(t_img *img, int x, int y, int color)
{
	char	*pixel;
	int		i;

	if (x >= WIDTH || y >= HEIGHT)
		return ;
	if (x < 0 || y < 0)
		return ;
	i = img->bpp - 8;
	pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
	while (i >= 0)
	{
		if (img->endian != 0)
			*pixel++ = (color >> i) & 0xFF;
		else
			*pixel++ = (color >> (img->bpp - 8 - i)) & 0xFF;
		i -= 8;
	}
}

int	render_background(t_img *img, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < HEIGHT)
	{
		j = 0;
		while (j < WIDTH)
		{
			img_pix_put(img, j++, i, color);
		}
		++i;
	}
	return (0);
}

float	pseudorand(t_data *data)
{
	unsigned int	ret;
	unsigned int	result;

	ret = data->rand;
	ret = ret * 747796405 + 2891336453;
	result = ((ret >> ((ret >> 28) + 4)) ^ ret) * 277803737;
	result = (result >> 22) ^ result;
	if (data->rand == 4294967295)
		data->rand = 0;
	data->rand++;
	return (((float) result / 4294967295));
}

t_Vec3	vec3rand(double min, double max, t_data *data)
{
	t_Vec3	ret;
	double	amp;

	amp = max - min;
	ret.x = pseudorand(data) * amp + min;
	ret.y = pseudorand(data) * amp + min;
	ret.z = pseudorand(data) * amp + min;
	return (ret);
}

t_Vec3	random_in_unit_sphere(t_data *data)
{
	t_Vec3	p;

	while (1)
	{
		p = vec3rand(-1, 1, data);
		if (vec3length2(p) >= 1)
			continue ;
		return (p);
	}
}

t_Vec3 Lambertian_random_ray(t_Vec3 normal, t_data *data)
{
	t_Vec3	random;
	t_Vec3	target;

	random = random_in_unit_sphere(data);
	target = addvec3(normal, random);
	target = unit_vec3(target);
	return (target);
}


t_hit	hit_sphere(t_sphere sphere, t_Ray ray, float t_min, float t_max)
{
	t_Vec3	oc;
	t_Vec3	abc;
	t_hit	hit;
	double	discriminant;
	double	temp;

	oc = subvec3(ray.orig, sphere.pos);
	abc.x = vec3length2(ray.dir);
	abc.y = dot(oc, ray.dir);
	abc.z = vec3length2(oc) - pow(sphere.rad, 2);
	discriminant = pow(abc.y, 2) - abc.x * abc.z;
	hit.mat = sphere.mat;
	if (discriminant > 0)
	{
		temp = (-abc.y - sqrt(discriminant)) / abc.x;
		if (temp < t_max && temp > t_min)
		{
			hit.t = temp;
			hit.p = vecat(ray, hit.t);
			hit.norm = scalevec3(subvec3(hit.p, sphere.pos), 1 / sphere.rad);
			hit.hit = 1;
			return (hit);
		}
		temp = (-abc.y + sqrt(discriminant)) / abc.x;
		if (temp < t_max && temp > t_min)
		{
			hit.t = temp;
			hit.p = vecat(ray, hit.t);
			hit.norm = scalevec3(subvec3(hit.p, sphere.pos), 1 / sphere.rad);
			hit.hit = 1;
			return (hit);
		}
	}
	hit.hit = 0;
	return (hit);
}

t_hit	hit_plane(t_plane plane, t_Ray ray, float t_min, float t_max)
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
			hit.hit = 1;
			hit.mat = plane.mat;
			return (hit);
		}
	}
	hit.hit = 0;
	return (hit);
}

t_hit	hit_cylinder(t_cylinder cylinder, t_Ray ray, float t_min, float t_max)
{
	t_hit	hit;
	t_Vec3	oc;
	t_Vec3	abc;
	double	discriminant;
	double	temp;

	oc = subvec3(ray.orig, cylinder.pos);
	abc.x = vec3length2(ray.dir) - pow(dot(ray.dir, cylinder.rot), 2);
	abc.y = 2 * (dot(oc, ray.dir) - dot(ray.dir, cylinder.rot) * dot(oc, cylinder.rot));
	abc.z = vec3length2(oc) - pow(dot(oc, cylinder.rot), 2) - pow(cylinder.rad, 2);
	discriminant = pow(abc.y, 2) - 4 * abc.x * abc.z;
	hit.mat = cylinder.mat;
	if (discriminant > 0)
	{
		temp = (-abc.y - sqrt(discriminant)) / (2 * abc.x);
		if (temp < t_max && temp > t_min)
		{
			hit.t = temp;
			hit.p = vecat(ray, hit.t);
			hit.norm = scalevec3(subvec3(hit.p, vec3(lerp(cylinder.pos.x, hit.p.x, cylinder.rot.x), lerp(cylinder.pos.y, hit.p.y, cylinder.rot.y), lerp(cylinder.pos.z, hit.p.z, cylinder.rot.z))), 1 / cylinder.rad);
			hit.hit = 1;
			return (hit);
		}
		temp = (-abc.y + sqrt(discriminant)) / (2 * abc.x);\
		if (temp < t_max && temp > t_min)
		{
			hit.t = temp;
			hit.p = vecat(ray, hit.t);
			hit.norm = scalevec3(subvec3(hit.p, vec3(cylinder.pos.x, hit.p.y, cylinder.pos.z)), 1 / cylinder.rad);
			hit.hit = 1;
			return (hit);
		}
	}
	hit.hit = 0;
	return (hit);
}

t_Ray	newray(t_Vec3 orig, t_Vec3 dir)
{
	t_Ray	ray;

	ray.orig = orig;
	ray.dir = dir;
	return (ray);
}

t_Col	computesky(t_Vec3 dir)
{
	float	grad;
	t_Col	col;
	float	strengh;
	t_Vec3	sun_pos;
	strengh = 2;
	sun_pos = vec3(1, 0.5, 0);
	grad = 0.5 * (dir.y + 1.0);
	grad = (1.0 - grad) * 0 + grad * strengh;
	if (dir.y > 0)
	{
		col = col4(0, strengh - (grad * 4 / 5), strengh
				- (grad * 6 / 10), strengh - 0.1);
		if (dot(unit_vec3(sun_pos), unit_vec3(dir)) > 0.99)
			col = addcol(col, col4(1, 100, 100, 80));
	}
	if (dir.y <= 0)
		col = col4(0, 0.5, 0.5, 0.5);
	return (col);
}

t_Vec3	reflect(t_Vec3 v, t_Vec3 n)
{
	double	val;
	t_Vec3	ret;

	val = dot(n, v) * 2;
	ret = subvec3(v, scalevec3(n, val));
	ret = scalevec3(ret, 1);
	return (ret);
}

float	fresnel(t_hit hit, t_Ray ray)
{
	return (saturate((hit.mat.smooth * (1
					- saturate(-dot(hit.norm, ray.dir))))));
}

t_Vec3	lerpvec3(t_Vec3 u, t_Vec3 v, float val)
{
	t_Vec3	ret;

	ret.x = v.x * val + u.x * (1 - val);
	ret.y = v.y * val + u.y * (1 - val);
	ret.z = v.z * val + u.z * (1 - val);
	return (ret);
}

t_Col	raycol(t_Ray ray, t_data *data, int depth)
{
	t_hit	hit;
	t_hit	hit_saved;
	float	t_max;
	int		hitted;
	int		i;
	t_Vec3	target;

	if (depth <= 0)
		return (col4(0, 0, 0, 0));
	t_max = 100;
	i = 0;
	hitted = 0;
	while (i < data->spherenbr)
	{
		hit = hit_sphere(data->sphere[i], ray, 0.001, t_max);
		if (hit.hit)
		{
			t_max = hit.t;
			hit_saved.norm = hit.norm;
			hit_saved.p = hit.p;
			hit_saved.t = hit.t;
			hit_saved.mat = hit.mat;
			hitted = 1;
		}
		i++;
	}
	i = 0;
	while (i < data->planenbr)
	{	
		hit = hit_plane(data->plane[i], ray, 0.001, t_max);
		if (hit.hit)
		{
			t_max = hit.t;
			hit_saved.norm = hit.norm;
			hit_saved.p = hit.p;
			hit_saved.t = hit.t;
			hit_saved.mat = hit.mat;
			hitted = 1;
		}
		i++;
	}
	i = 0;
	while (i < data->cylindernbr)
	{	
		hit = hit_cylinder(data->cylinder[i], ray, 0.001, t_max);
		if (hit.hit)
		{
			t_max = hit.t;
			hit_saved.norm = hit.norm;
			hit_saved.p = hit.p;
			hit_saved.t = hit.t;
			hit_saved.mat = hit.mat;
			hitted = 1;
		}
		i++;
	}
	if (hitted)
	{
		hit = hit_saved;
		if (hit.mat.col.t > 0)
			return (hit.mat.col);
		t_Vec3 diffuse = addvec3(hit.p, Lambertian_random_ray(hit.norm, data));
		t_Vec3 specular = addvec3(hit.p, reflect(ray.dir, hit.norm));
		int isSpecular = hit.mat.metal >= pseudorand(data);
		target = lerpvec3(diffuse, specular, hit.mat.smooth * isSpecular);
		if (!isSpecular)
			return (mulcol(scalecol(raycol(newray(hit.p, subvec3(target, hit.p)), data, depth - 1), 0.5), hit.mat.col));
		else
			return (mulcol(scalecol(raycol(newray(hit.p, subvec3(target, hit.p)), data, depth - 1), 0.5), hit.mat.col));
	}
	return (computesky(unit_vec3(ray.dir)));
}

int	render(t_data *data)
{
	t_Int2	s;
	t_Vec3	u;
	t_Tri	hvl;
	t_Ray	ray;
	t_Col	col;
	float	weight;

	s = int2(0, 0);
	ray.orig = data->cam.pos;
	ray.dir = vec3(0, 0, 0);
	hvl.pos1 = vec3(data->cam.vwi, 0, 0);
	hvl.pos2 = vec3(0, -data->cam.vhe, 0);
	hvl.pos3 = subvec3(subvec3(subvec3(ray.orig, scalevec3(hvl.pos1, 0.5)), scalevec3(hvl.pos2, 0.5)), vec3(0, 0, data->cam.focal));
	render_background(&data->img, 0);
	while (s.y < HEIGHT)
	{
		while (s.x < WIDTH)
		{
			u.x = ((double) s.x + pseudorand(data) * 2 - 1) / (WIDTH - 1);
			u.y = ((double) s.y + pseudorand(data) * 2 - 1) / (HEIGHT - 1);
			ray.dir = addvec3(addvec3(hvl.pos3, scalevec3(hvl.pos1, u.x)), scalevec3(hvl.pos2, u.y));
			weight = 1.0 / ((float) data->frame + 1);
			if (data->frame == 0)
				data->cimg[s.y][s.x] = addcol(col4(0, 0, 0, 0), raycol(ray, data, data->frame));
			else
				data->cimg[s.y][s.x] = addcol(scalecol(data->cimg[s.y][s.x], 1 - weight), scalecol(raycol(ray, data, 1 + data->bounces), weight));
			img_pix_put(&data->img, s.x++, s.y, create_trgb(data->cimg[s.y][s.x]));
		}
		s = int2(0, s.y + 1);
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img.mlx_img, 0, 0);
	printf("frame : %d, %f\n", data->frame, data->cimg[0][0].b);
	data->frame++;
	return (0);
}
