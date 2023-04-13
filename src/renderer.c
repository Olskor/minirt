/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jauffret <jauffret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 01:13:30 by olskor            #+#    #+#             */
/*   Updated: 2023/04/13 19:44:18 by jauffret         ###   ########.fr       */
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

float hit_sphere(t_sphere sphere, t_Ray ray)
{
    t_Vec3	oc;
	t_Vec3	abc;
	double	discriminant;
	
	oc = subvec3(ray.orig, sphere.pos);
    abc.x = dot(ray.dir, ray.dir);
    abc.y = 2.0 * dot(oc, ray.dir);
    abc.z = dot(oc, oc) - pow(sphere.rad, 2);
    discriminant = pow(abc.y, 2) - 4 * abc.x * abc.z;
	if (discriminant < 0)
        return -1.0;
	else
        return (-abc.y - sqrt(discriminant) ) / (2.0 * abc.x);
}

int raycol(t_Ray ray, t_data *data)
{
	float	t;
	t_Vec3	n;
	int		i;

	t = hit_sphere(data->sphere[0], ray);
    if (t > 0.0)
	{
        n = unit_vec3(subvec3(vecat(ray, t), vec3(0,0,-1)));
        return (create_trgb(0, 128 * (n.x + 1), 128 * (n.y + 1), 128 * (n.z + 1)));
    }
	ray.dir = unit_vec3(ray.dir);
	t = 0.5 * (ray.dir.y + 1.0);
	i = (int)(1.0 - t) * 0 + t * 255;
	return (create_trgb(0, 128 + (i / 2), 178 + (i * 3/10), 255));
}

int	render(t_data *data)
{
	t_Int2	s;
	t_Vec3	u;
	t_Tri	hvl;
	t_Ray	ray;

	s = int2(0, 0);
	ray.orig = data->cam.pos;
	hvl.pos1 = vec3(data->cam.vwi, 0, 0);
	hvl.pos2 = vec3(0, data->cam.vhe, 0);
	hvl.pos3 = subvec3(subvec3(subvec3(ray.orig, scalevec3(hvl.pos1, 0.5)), scalevec3(hvl.pos2, 0.5)), vec3(0, 0, data->cam.focal));
	render_background(&data->img, 0);
	while (s.y < data->he)
	{
		while (s.x < data->wi)
		{
			u.x = (double) s.x / (data->wi - 1);
			u.y = (double) s.y / (data->he - 1);
			ray.dir = addvec3(addvec3(hvl.pos3, scalevec3(hvl.pos1, u.x)), scalevec3(hvl.pos2, u.y));
			img_pix_put(&data->img, s.x++, s.y, raycol(ray, data));
		}
		s = int2(0, s.y + 1);
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img.mlx_img, 0, 0);
	return (0);
}
