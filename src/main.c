/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olskor <olskor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 17:07:13 by jauffret          #+#    #+#             */
/*   Updated: 2023/12/31 15:55:24 by olskor           ###   ########.fr       */
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
	data.bounces = MAX_BOUNCES;
	data.wi = WIDTH;
	data.he = HEIGHT;
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
	create_config(argv[1], &data);
	data.cam->aspect = (float) data.wi / (float) data.he;
	mlx_loop(data.mlx);
	return (0);
}
