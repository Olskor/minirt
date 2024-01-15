/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olskor <olskor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 17:07:13 by jauffret          #+#    #+#             */
/*   Updated: 2024/01/15 09:41:06 by olskor           ###   ########.fr       */
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
	data->cimg = ft_calloc(sizeof(t_Col *), (data->he +1));
	while (i < data->he)
	{
		data->cimg[i] = malloc(sizeof(t_Col) * data->wi);
		i++;
	}
}

void	create_texture(t_data *data);

int	main2(t_data *data)
{
	data->img.mlx_img = mlx_new_image(data->mlx, data->wi, data->he);
	data->img.addr = mlx_get_data_addr(data->img.mlx_img, &data->img.bpp,
			&data->img.line_len, &data->img.endian);
	data->img.wi = data->wi;
	data->img.he = data->he;
	hook_setup(data);
	data->cam->aspect = (float) data->wi / (float) data->he;
	create_texture(data);
	mlx_loop(data->mlx);
	return (0);
}

void	_valide_ext_fichier(char *p, t_data *data)
{
	char	*pp;

	pp = ft_strrchr(p, '.');
	if (pp && *pp && *pp++ == '.' && *pp++ == 'r' && *pp++ == 't' && (!*pp))
		return ;
	else
	{
		printf("Error\n%s\n", "Extension du fichier invalide.");
		free (data);
		exit (-1);
	}
}

int	main(int argc, char **argv)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (argc <= 1)
		return (write(2, "error: not enough argument\n", 27));
	_valide_ext_fichier(argv[1], data);
	data->bounces = MAX_BOUNCES;
	create_config(argv[1], data);
	if (data->b_parse_error || !_valide_data(data))
	{
		cleanup(data);
		exit(-1);
	}
	data->mlx = mlx_init();
	if (!data->mlx)
		return (write(2, "Error\nerror: memory\n", 14));
	alloccimg(data);
	data->win = mlx_new_window(data->mlx, data->wi, data->he, "MiniRT");
	if (!data->win)
	{
		free(data->win);
		return (1);
	}
	return (main2(data));
}
