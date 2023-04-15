/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olskor <olskor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 17:07:13 by jauffret          #+#    #+#             */
/*   Updated: 2023/04/15 02:48:07 by olskor           ###   ########.fr       */
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
	data.wi = 800;
	data.he = 600;
	data.rand = 0;
	data.bounces = 10;
	data.cam.aspect = (float) data.wi / data.he;
	data.cam.pos = vec3(0, 0.0, 0.0);
	data.sphere = malloc(sizeof(t_sphere) * 5);
	data.sphere[0].pos = vec3(-0.2, 0.0, -1.5);
	data.sphere[0].rad = 0.5;
	data.sphere[0].mat.col = col4(0, 1.0, 0.05, 0.05);
	data.sphere[0].mat.smooth = 0.0;
	data.sphere[1].pos = vec3(0.0, -100.5, -1.5);
	data.sphere[1].rad = 100.0;
	data.sphere[1].mat.col = col4(0, 0.05, 1.0, 0.3);
	data.sphere[1].mat.smooth = 0.0;
	data.sphere[2].pos = vec3(0.1, -0.4, -1.0);
	data.sphere[2].rad = 0.1;
	data.sphere[2].mat.col = col4(1, 0, 0, 50);
	data.sphere[2].mat.smooth = 0.0;
	data.sphere[3].pos = vec3(0.5, -0.3, -1.5);
	data.sphere[3].rad = 0.2;
	data.sphere[3].mat.col = col4(0, 0.98, 0.98, 0.3);
	data.sphere[3].mat.smooth = 1.0;
	data.sphere[4].pos = vec3(500, 300, -150);
	data.sphere[4].rad = 50;
	data.sphere[4].mat.col = col4(1, 200, 200, 200);
	data.sphere[4].mat.smooth = 0.0;
	data.frame = 0;
	alloccimg(&data);
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
