/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_fred.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olskor <olskor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 17:07:13 by jauffret          #+#    #+#             */
/*   Updated: 2023/12/30 13:46:56 by olskor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"
#include "libft.h"

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc <= 1)
		return (write(2, "error: not enough argument\n", 27));
	data = create_config(argv[1]);
	cleanup(data);
//	data.mlx = mlx_init();
//	if (!data.mlx)
//		return (write(2, "error: memory\n", 14));
//
//
//	alloccimg(&data);
//	data.win = mlx_new_window(data.mlx, data.wi, data.he, "c'est pas fdf fdp");
//	if (!data.win)
//	{
//		free(data.win);
//		return (1);
//	}
//	data.img.mlx_img = mlx_new_image(data.mlx, data.wi, data.he);
//	data.img.addr = mlx_get_data_addr(data.img.mlx_img, &data.img.bpp,
//			&data.img.line_len, &data.img.endian);
//	data.img.wi = data.wi;
//	data.img.he = data.he;
//	hook_setup(&data);
//
//	t_Tex	*rainbow = load_img("rainbow.xpm", &data);
//	t_Tex	*checker = load_img("checker.xpm", &data);
//	t_Tex	*checker_height = load_img("checker_height.xpm", &data);
//	t_Tex	*earth = load_img("earth.xpm", &data);
//	t_Tex	*earth_bump = load_img("earth_bump.xpm", &data);
//	t_Tex	*earth_pbr = load_img("earth_pbr.xpm", &data);
//
//
//	mlx_loop(data.mlx);
	return (0);
}
