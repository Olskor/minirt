/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olskor <olskor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 17:07:13 by jauffret          #+#    #+#             */
/*   Updated: 2023/04/14 00:18:52 by olskor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	close_window(t_data *data)
{
	mlx_destroy_image(data->mlx, data->img.mlx_img);
	mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	exit(0);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc <= 1)
		return (write(2, "error: not enough argument\n", 27));
	data.mlx = mlx_init();
	if (!data.mlx)
		return (write(2, "error: memory\n", 14));
	data.wi = 800;
	data.he = 600;
	data.cam.aspect = (float) data.wi / data.he;
	data.cam.pos = vec3(0, 0, 0);
	data.sphere = malloc(sizeof(t_sphere) * 2);
	data.sphere[0].pos = vec3(0.0, 0.0, -1.0);
	data.sphere[0].rad = 0.5;
	data.sphere[1].pos = vec3(0.0, 100.0, -1.0);
	data.sphere[1].rad = 100;
	data.frame = 0;
	data.win = mlx_new_window(data.mlx, data.wi, data.he, "fdf");
	if (!data.win)
	{
		free(data.win);
		return (1);
	}
	data.img.mlx_img = mlx_new_image(data.mlx, WIDTH, HEIGHT);
	data.img.addr = mlx_get_data_addr(data.img.mlx_img, &data.img.bpp,
			&data.img.line_len, &data.img.endian);
	hook_setup(&data);
	mlx_loop(data.mlx);
	return (0);
}
