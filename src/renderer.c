/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olskor <olskor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 01:13:30 by olskor            #+#    #+#             */
/*   Updated: 2023/12/21 20:17:28 by olskor           ###   ########.fr       */
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
	data->cam.v_ul = subvec3(data->cam.pos, subvec3(scalevec3(data->cam.w, data->cam.focal), subvec3(scalevec3(data->cam.v_u, -0.5), scalevec3(data->cam.v_v, 0.5))));
    data->cam.pix00 = data->cam.v_ul;

	render(data);
	return (0);
}

void	img_pix_put(t_img *img, int x, int y, int color)
{
	char	*pixel;
	int		i;

	if (x >= img->wi || y >= img->he)
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
	while (i < img->he)
	{
		j = 0;
		while (j < img->wi)
		{
			img_pix_put(img, j++, i, color);
		}
		++i;
	}
	return (0);
}

t_hit	hit_light(t_light light, t_Ray ray, float t_min, float t_max)
{
	t_Vec3	oc;
	t_Vec3	abc;
	t_hit	hit;
	double	discriminant;
	double	temp;

	oc = subvec3(ray.orig, light.pos);
	abc.x = vec3length2(ray.dir);
	abc.y = dot(oc, ray.dir);
	abc.z = vec3length2(oc) - pow(0.1, 2);
	discriminant = pow(abc.y, 2) - abc.x * abc.z;
	hit.mat.col = scalecol(light.col, light.intensity);
	hit.mat.col.t = 1;
	hit.mat.smooth = 0;
	hit.mat.metal = 0;
	hit.mat.refr = 0;
	if (discriminant > 0)
	{
		temp = (-abc.y - sqrt(discriminant)) / abc.x;
		if (temp < t_max && temp > t_min)
		{
			hit.t = temp;
			hit.p = vecat(ray, hit.t);
			hit.norm = scalevec3(subvec3(hit.p, light.pos), 1 / 0.1);
			hit.hit = 1;
			return (hit);
		}
		temp = (-abc.y + sqrt(discriminant)) / abc.x;
		if (temp < t_max && temp > t_min)
		{
			hit.t = temp;
			hit.p = vecat(ray, hit.t);
			hit.norm = scalevec3(subvec3(hit.p, light.pos), 1 / 0.1);
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
		if (dot(unit_vec3(sky.sun), unit_vec3(dir)) > 0.99)
			col = addcol(col, col4(1, sky.intensity * 100, sky.intensity * 100, sky.intensity * 80));
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
					- saturate(1 * -dot(hit.norm, ray.dir))))));
}

t_Vec3	lerpvec3(t_Vec3 u, t_Vec3 v, float val)
{
	t_Vec3	ret;

	ret.x = v.x * val + u.x * (1 - val);
	ret.y = v.y * val + u.y * (1 - val);
	ret.z = v.z * val + u.z * (1 - val);
	return (ret);
}

t_Col	raycol(t_Ray ray, t_data *data, int depth);

t_Col	pb_shading(t_Ray ray, t_data *data, t_hit hit, int depth)
{
	t_Vec3	target;
	t_Vec3	diffuse;
	t_Vec3	specular;
	int		isspecular;

	if (hit.hit)
	{
		if (hit.mat.col.t > 0)
			return (hit.mat.col);
		diffuse = addvec3(hit.p, lambertian_random_ray(hit.norm, data));
		specular = addvec3(hit.p, reflect(ray.dir, hit.norm));
		isspecular = hit.mat.metal >= pseudorand(data);
		target = lerpvec3(diffuse, specular, hit.mat.smooth * isspecular);
		if (!isspecular)
			return (mulcol(scalecol(raycol(newray(hit.p, subvec3(target, hit.p)), data, depth - 1), 0.5), hit.mat.col));
		else
			return (mulcol(scalecol(raycol(newray(hit.p, subvec3(target, hit.p)), data, depth - 1), 0.5), hit.mat.col));
	}
	if (data->sky.active)
		return (computesky(unit_vec3(ray.dir), data->sky));
	else if (depth < 1 + data->bounces)
		return (data->ambient);
	return (col4(0, 0, 0, 0));
}

t_Col	raycol(t_Ray ray, t_data *data, int depth)
{
	t_hit	hit;

	if (depth <= 0)
		return (data->ambient);
	hit.t_max = 100;
	hit.hit = 0;
	hit = hit_sphere(data, ray, hit);
	hit = hit_plane(data, ray, hit);
	hit = hit_cylinder(data, ray, hit);
	return (pb_shading(ray, data, hit, depth));
}

void	save_img(t_data *data)
{
	int		fd;
	int		i;
	int		j;
	char	*filename;
	char	*tmp;

	tmp = ft_itoa(data->frame);
	data->frame++;
	filename = ft_strjoin("img/", tmp);
	filename = ft_strjoin(filename, ".ppm");
	fd = open(filename, O_CREAT | O_WRONLY, 0666);
	write(fd, "P3\n", 3);
	free(tmp);
	tmp = ft_itoa(data->wi);
	write(fd, tmp, ft_strlen(tmp));
	write(fd, " ", 1);
	free(tmp);
	tmp = ft_itoa(data->he);
	write(fd, tmp, ft_strlen(tmp));
	write(fd, "\n", 1);
	i = 0;
	while (i < data->he)
	{
		j = 0;
		while (j < data->wi)
		{
			tmp = ft_itoa((int) (aces(data->cimg[i][j].b) * 255.99));
			write(fd, tmp, ft_strlen(tmp));
			write(fd, "\n", 1);
			free(tmp);
			tmp = ft_itoa((int) (aces(data->cimg[i][j].r) * 255.99));
			write(fd, tmp, ft_strlen(tmp));
			write(fd, "\n", 1);
			free(tmp);
			tmp = ft_itoa((int) (aces(data->cimg[i][j].g) * 255.99));
			write(fd, tmp, ft_strlen(tmp));
			write(fd, "\n", 1);
			free(tmp);
			j++;
		}
		i++;
	}
	free(filename);
	close(fd);
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
			ray.dir = (subvec3(addvec3(pixpos, scalevec3(random_in_unit_sphere(data), 0.005f)), data->cam.pos));
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
