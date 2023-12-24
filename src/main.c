/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olskor <olskor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 17:07:13 by jauffret          #+#    #+#             */
/*   Updated: 2023/12/24 23:09:04 by olskor           ###   ########.fr       */
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

	data.rand = 0;
	data.bounces = MAX_BOUNCES;
	data.frame = 0;
	data.sample = 0;
	data.wi = WIDTH;
	data.he = HEIGHT;

	data.cam.aspect = (float) data.wi / (float) data.he;
	data.cam.pos = vec3(2, 2, 3);
	data.cam.rot = vec3(2, 0, -1);
	data.cam.vup = vec3(0, 1, 0);
	data.cam.fov = 70;

	data.ambient = col4(0, 0.1, 0.1, 0.1);

	data.sky.active = 1;
	data.sky.sun = vec3(-1, -1, 0);
	data.sky.intensity = 2;

	data.meshnbr = 0;
	data.mesh = malloc(sizeof(t_mesh) * data.meshnbr);

	/*data.mesh[0].trinbr = 0;
	data.mesh[0] = read_obj("icosphere.obj");
	data.mesh[0].mat.col = col4(0, 1, 1, 1);
	data.mesh[0].mat.smooth = 0.0;
	data.mesh[0].mat.metal = 0.0;
	data.mesh[0].pos = vec3(-0.6, -0.5, -1);
	data.mesh[0].dir = vec3(0, 0, 1);
	data.mesh[0].up = vec3(0, 1, 0);
	data.mesh[0].scale = vec3(1, 1, 1);
	data.mesh[0] = rotate_mesh(data.mesh[0]);
	data.mesh[0] = scale_mesh(data.mesh[0]);
	data.mesh[0] = translate_mesh(data.mesh[0]);

	data.mesh[1].trinbr = 0;
	data.mesh[1] = read_obj("plane.obj");
	data.mesh[1].mat.col = col4(1, 1, 1, 1);
	data.mesh[1].mat.smooth = 0.0;
	data.mesh[1].mat.metal = 0.0;
	data.mesh[1].pos = vec3(0, 0.99, -1);
	data.mesh[1].dir = vec3(0, 0, 1);
	data.mesh[1].up = vec3(0, 1, 0);
	data.mesh[1].scale = vec3(0.3, 0.3, 0.3);
	data.mesh[1] = rotate_mesh(data.mesh[1]);
	data.mesh[1] = scale_mesh(data.mesh[1]);
	data.mesh[1] = translate_mesh(data.mesh[1]);*/

	data.lightnbr = 0;
	data.light = malloc(sizeof(t_light) * data.lightnbr);

	/*data.light[0].pos = vec3(-0.5, 0, -0.3);
	data.light[0].col = col4(1, 1, 0, 1);
	data.light[0].intensity = 1;

	data.light[1].pos = vec3(0.5, 0, -0.3);
	data.light[1].col = col4(1, 0, 1, 1);
	data.light[1].intensity = 1;*/

	data.spherenbr = 0;
	data.sphere = malloc(sizeof(t_sphere) * data.spherenbr);

	/*data.sphere[0].pos = vec3(0.6, -0.2, -1);
	data.sphere[0].rad = 0.3;
	data.sphere[0].mat.col = col4(0, 1, 1, 1);
	data.sphere[0].mat.smooth = 0.95;
	data.sphere[0].mat.metal = 1.0;*/

	data.planenbr = 1;
	data.plane = malloc(sizeof(t_plane) * data.planenbr);

	data.plane[0].pos = vec3(0, -0.5, 0);
	data.plane[0].norm = vec3(0, 1, 0);
	data.plane[0].mat.col = col4(0, 1, 1, 1);
	data.plane[0].mat.smooth = 0.8;
	data.plane[0].mat.metal = 0.1;

	/*data.plane[1].pos = vec3(0, 1, 0);
	data.plane[1].norm = vec3(0, -1, 0);
	data.plane[1].mat.col = col4(0, 1, 1, 1);
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

	data.cylindernbr = 7;
	data.cylinder = malloc(sizeof(t_cone) * data.cylindernbr);

	data.cylinder[0].pos = vec3(-1, 0, -1.2);
	data.cylinder[0].dir = unit_vec3(vec3(0, -1, -1));
	data.cylinder[0].rad = 0.4;
	data.cylinder[0].h = 1;
	data.cylinder[0].mat.col = col4(0, 1, 0, 1);
	data.cylinder[0].mat.smooth = 0.0;
	data.cylinder[0].mat.metal = 0.1;

	data.cylinder[1].pos = vec3(0, 0, -1.2);
	data.cylinder[1].dir = unit_vec3(vec3(0, 1, -1));
	data.cylinder[1].rad = 0.05;
	data.cylinder[1].h = 0.1;
	data.cylinder[1].mat.col = col4(0, 1, 0, 0);
	data.cylinder[1].mat.smooth = 0.0;
	data.cylinder[1].mat.metal = 0.1;

	data.cylinder[2].pos = vec3(1, 0, -1.2);
	data.cylinder[2].dir = unit_vec3(vec3(1, 0, -1));
	data.cylinder[2].rad = 0.4;
	data.cylinder[2].h = 0.2;
	data.cylinder[2].mat.col = col4(0, 1, 0.5, 0.5);
	data.cylinder[2].mat.smooth = 0.0;
	data.cylinder[2].mat.metal = 0.1;

	data.cylinder[3].pos = vec3(2, 0, -1.2);
	data.cylinder[3].dir = unit_vec3(vec3(-1, 0, -1));
	data.cylinder[3].rad = 0.1;
	data.cylinder[3].h = 2;
	data.cylinder[3].mat.col = col4(0, 0, 1, 1);
	data.cylinder[3].mat.smooth = 1.0;
	data.cylinder[3].mat.metal = 1.0;

	data.cylinder[4].pos = vec3(3, 0, -1.2);
	data.cylinder[4].dir = unit_vec3(vec3(0, -1, 1));
	data.cylinder[4].rad = 0.2;
	data.cylinder[4].h = 1;
	data.cylinder[4].mat.col = col4(0, 1, 0, 0);
	data.cylinder[4].mat.smooth = 0.0;
	data.cylinder[4].mat.metal = 0.1;

	data.cylinder[5].pos = vec3(4, 0, -1.2);
	data.cylinder[5].dir = unit_vec3(vec3(0, 1, 1));
	data.cylinder[5].rad = 0.4;
	data.cylinder[5].h = 1;
	data.cylinder[5].mat.col = col4(0, 0, 0, 1);
	data.cylinder[5].mat.smooth = 1.0;
	data.cylinder[5].mat.metal = 1.0;

	data.cylinder[6].pos = vec3(5, 0, -1.2);
	data.cylinder[6].dir = unit_vec3(vec3(1, 0, 1));
	data.cylinder[6].rad = 0.2;
	data.cylinder[6].h = 1;
	data.cylinder[6].mat.col = col4(0, 0, 1, 0);
	data.cylinder[6].mat.smooth = 0.0;
	data.cylinder[6].mat.metal = 0.1;

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
