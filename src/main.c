/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olskor <olskor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 17:07:13 by jauffret          #+#    #+#             */
/*   Updated: 2023/12/22 18:31:31 by olskor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "libft.h"

int	close_window(t_data *data)
{
	mlx_destroy_image(data->mlx, data->img.mlx_img);
	mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	exit(0);
}

void	alloccimg(t_data *data)
{
	int	i;

	i = 0;
	data->cimg = malloc(sizeof(t_Col *) * data->he);
	while (i < data->he)
	{
		data->cimg[i] = malloc(sizeof(t_Col) * data->wi);
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc <= 1)
		return (write(2, "error: not enough argument\n", 27));
	data.mlx = mlx_init();
	if (!data.mlx)
		return (write(2, "error: memory\n", 14));
//	fred
//	load(argv[1], &data);
	data.rand = 0;
	data.bounces = MAX_BOUNCES;
	data.frame = 0;
	data.sample = 0;
	data.wi = WIDTH;
	data.he = HEIGHT;

	data.cam.aspect = (float) data.wi / (float) data.he;
	data.cam.pos = vec3(-2, 1, 1);
	data.cam.rot = vec3(0, 0, -1);
	data.cam.vup = vec3(0, 1, 0);
	data.cam.fov = 70;

	data.ambient = col4(0, 0.1, 0.1, 0.1);

	data.sky.active = 0;
	data.sky.sun = vec3(-1, -1, 0);
	data.sky.intensity = 2;

	data.lightnbr = 2;
	data.light = malloc(sizeof(t_light) * data.lightnbr);

	data.light[0].pos = vec3(0, 1, 0);
	data.light[0].col = col4(0, 1, 1, 1);
	data.light[0].intensity = 1;

	data.light[1].pos = vec3(0, 1, -1);
	data.light[1].col = col4(0, 0, 1, 1);
	data.light[1].intensity = 1;

	data.spherenbr = 4;
	data.sphere = malloc(sizeof(t_sphere) * data.spherenbr);

	data.sphere[0].pos = vec3(-0.2, 0.0, -1.5);
	data.sphere[0].rad = 0.5;
	data.sphere[0].mat.col = col4(0, 1.0, 0.05, 0.05);
	data.sphere[0].mat.smooth = 0.7;
	data.sphere[0].mat.metal = 0.1;

	data.sphere[1].pos = vec3(0.3, -0.4, -1.0);
	data.sphere[1].rad = 0.1;
	data.sphere[1].mat.col = col4(0, 0, 0.1, 1);
	data.sphere[1].mat.smooth = 0.0;
	data.sphere[1].mat.metal = 0.0;

	data.sphere[2].pos = vec3(1.0, 0.0, -1.5);
	data.sphere[2].rad = 0.5;
	data.sphere[2].mat.col = col4(0, 0.98, 0.98, 0.3);
	data.sphere[2].mat.smooth = 0.85;
	data.sphere[2].mat.metal = 1.0;

	data.sphere[3].pos = vec3(-0.3, -0.4, -1);
	data.sphere[3].rad = 0.1;
	data.sphere[3].mat.col = col4(0, 1, 1, 1);
	data.sphere[3].mat.smooth = 0.75;
	data.sphere[3].mat.metal = 1.0;

	data.planenbr = 1;
	data.plane = malloc(sizeof(t_plane) * data.planenbr);

	data.plane[0].pos = vec3(0, -0.5, 0);
	data.plane[0].norm = vec3(0, 1, 0);
	data.plane[0].mat.col = col4(0, 1, 1, 1);
	data.plane[0].mat.smooth = 0.0;
	data.plane[0].mat.metal = 0.0;

	/*data.plane[1].pos = vec3(0, 1, 0);
	data.plane[1].norm = vec3(0, -1, 0);
	data.plane[1].mat.col = col4(1, 1, 1, 1);
	data.plane[1].mat.smooth = 0.0;
	data.plane[1].mat.metal = 0.0;

	data.plane[2].pos = vec3(-1, 0, 0);
	data.plane[2].norm = vec3(1, 0, 0);
	data.plane[2].mat.col = col4(0, 1, 0, 0);
	data.plane[2].mat.smooth = 0.0;
	data.plane[2].mat.metal = 0.0;

	data.plane[3].pos = vec3(1, 0, 0);
	data.plane[3].norm = vec3(-1, 0, 0);
	data.plane[3].mat.col = col4(0, 0, 1, 0);
	data.plane[3].mat.smooth = 0.0;
	data.plane[3].mat.metal = 0.0;

	data.plane[4].pos = vec3(0, 0, -2);
	data.plane[4].norm = vec3(0, 0, 1);
	data.plane[4].mat.col = col4(0, 1, 1, 1);
	data.plane[4].mat.smooth = 0.0;
	data.plane[4].mat.metal = 0.0;*/

	data.cylindernbr = 1;
	data.cylinder = malloc(sizeof(t_cone) * data.cylindernbr);
	data.cylinder[0].pos = vec3(1, 0, -1);
	data.cylinder[0].rad = 0.1;
	data.cylinder[0].h = 1;
	data.cylinder[0].dir = unit_vec3(vec3(1, 1, 0));
	data.cylinder[0].mat.col = col4(0, 1, 1, 1);
	data.cylinder[0].mat.smooth = 1.0;
	data.cylinder[0].mat.metal = 1.0;

	alloccimg(&data);
	data.win = mlx_new_window(data.mlx, data.wi, data.he, "c'est pas fdf fdp");
	if (!data.win)
	{
		free(data.win);
		return (1);
	}
	data.img.mlx_img = mlx_new_image(data.mlx, data.wi, data.he);
	data.img.addr = mlx_get_data_addr(data.img.mlx_img, &data.img.bpp,
			&data.img.line_len, &data.img.endian);
	data.img.wi = data.wi;
	data.img.he = data.he;
	hook_setup(&data);
	mlx_loop(data.mlx);
	return (0);
}
