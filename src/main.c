/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olskor <olskor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 17:07:13 by jauffret          #+#    #+#             */
/*   Updated: 2024/01/11 11:59:46 by olskor           ###   ########.fr       */
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
	cleanup(data);
	exit(0);
}

void	alloccimg(t_data *data)
{
	int	i;

	i = 0;
	data->cimg = ft_calloc(sizeof(t_Col *),  (data->he +1));
	while (i < data->he)
	{
		data->cimg[i] = malloc(sizeof(t_Col) * data->wi);
		i++;
	}
}

void	create_cube(t_data *data);

int	main(int argc, char **argv)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (argc <= 1)
		return (write(2, "error: not enough argument\n", 27));
	data->bounces = MAX_BOUNCES;
	data->wi = WIDTH;
	data->he = HEIGHT;
	create_config(argv[1], data);
	if (data->b_parse_error)
	{
		cleanup(data);
		exit(-1);
	}
	data->mlx = mlx_init();
	if (!data->mlx)
		return (write(2, "error: memory\n", 14));
	alloccimg(data);
	data->win = mlx_new_window(data->mlx, data->wi, data->he, "MiniRT de Fred et JB hahaha");
	if (!data->win)
	{
		free(data->win);
		return (1);
	}
	data->img.mlx_img = mlx_new_image(data->mlx, data->wi, data->he);
	data->img.addr = mlx_get_data_addr(data->img.mlx_img, &data->img.bpp,
			&data->img.line_len, &data->img.endian);
	data->img.wi = data->wi;
	data->img.he = data->he;
	hook_setup(data);
	data->cam->aspect = (float) data->wi / (float) data->he;
	create_cube(data);
	mlx_loop(data->mlx);
	return (0);
}
