/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olskor <olskor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 11:58:23 by olskor            #+#    #+#             */
/*   Updated: 2023/12/28 01:01:53 by olskor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_Tex	*checker_tex(void)
{
	t_Tex	*tex;
	int		i;
	int		j;

	tex = malloc(sizeof(t_Tex));
	tex->img = malloc(sizeof(t_Col *) * 9);
	tex->res = 9;
	i = 0;
	while (i < 9)
	{
		tex->img[i] = malloc(sizeof(t_Col) * 9);
		j = 0;
		while (j < 9)
		{
			if ((i + j) % 2 == 0)
				tex->img[i][j] = col4(0, 0.1, 0.1, 0.1);
			else
				tex->img[i][j] = col4(0, 1, 1, 1);
			j++;
		}
		i++;
	}
	return (tex);
}

t_Tex	*rainbowtex(void)
{
	t_Tex	*tex;
	int		i;
	int		j;

	tex = malloc(sizeof(t_Tex));
	tex->img = malloc(sizeof(t_Col *) * 9);
	tex->res = 9;
	i = 0;
	while (i < 9)
	{
		tex->img[i] = malloc(sizeof(t_Col) * 9);
		j = 0;
		while (j < 9)
		{
			if (i == 0)
				tex->img[i][j] = col4(0, 1, 0, 0);
			else if (i == 1)
				tex->img[i][j] = col4(0, 1, 0.5, 0);
			else if (i == 2)
				tex->img[i][j] = col4(0, 1, 1, 0);
			else if (i == 3)
				tex->img[i][j] = col4(0, 0, 1, 0);
			else if (i == 4)
				tex->img[i][j] = col4(0, 0, 1, 1);
			else if (i == 5)
				tex->img[i][j] = col4(0, 0, 0, 1);
			else if (i == 6)
				tex->img[i][j] = col4(0, 0.5, 0, 1);
			else if (i == 7)
				tex->img[i][j] = col4(0, 1, 0, 1);
			else if (i == 8)
				tex->img[i][j] = col4(0, 1, 0, 0.5);
			j++;
		}
		i++;
	}
	return (tex);
}

t_Col	get_texcol(t_Tex *tex, t_Vec3 uv)
{
	int		u;
	int		v;

	if (!tex->img)
		return (col4(0, 1, 1, 1));
	u = (int)(uv.x * (tex->res - 1));
	v = (int)(uv.y * (tex->res - 1));
	if (u < 0)
		u = 0;
	if (v < 0)
		v = 0;
	if (u > tex->res - 1)
		u = tex->res - 1;
	if (v > tex->res - 1)
		v = tex->res - 1;
	return (tex->img[u][v]);
}

int	img_pix_read(t_img *img, int x, int y)
{
	char	*pixel;
	int		i;
	int		col;

	if (x >= img->wi || y >= img->wi)
		return (0);
	if (x < 0 || y < 0)
		return (0);
	i = img->bpp - 8;
	pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
	col = 0;
	while (i >= 0)
	{
		if (img->endian != 0)
			col |= (*pixel++ & 0xFF) << i;
		else
			col |= (*pixel++ & 0xFF) << (img->bpp - 8 - i);
		i -= 8;
	}
	return (col);
}

t_Col	trgb_to_col(int trgb)
{
	t_Col	col;

	col.t = (trgb & (0xFF << 24)) >> 24;
	col.r = (trgb & (0xFF << 16)) >> 16;
	col.g = (trgb & (0xFF << 8)) >> 8;
	col.b = (trgb & (0xFF << 0)) >> 0;
	col = scalecol(col, (double)1 / 255);
	return (col);
}

t_Tex	*load_img(char *path, t_data *data)
{
	t_Tex	*tex;
	t_img	img;
	int		size;
	int		i;
	int		j;

	img.mlx_img = mlx_xpm_file_to_image(data->mlx, path, &size, &size);
	img.wi = size;
	if (!img.mlx_img)
		return (NULL);
	img.addr = mlx_get_data_addr(img.mlx_img, &img.bpp,
			&img.line_len, &img.endian);
	i = 0;
	j = 0;
	tex = malloc(sizeof(t_Tex));
	tex->img = malloc(sizeof(t_Col *) * size);
	tex->res = size;
	printf("size : %d\n", size);
	while (i < size)
	{
		tex->img[i] = malloc(sizeof(t_Col) * size);
		j = 0;
		while (j < size)
		{
			tex->img[i][j] = trgb_to_col(img_pix_read(&img, i, j));
			mlx_pixel_put(data->mlx, data->win, i, j, create_trgb(tex->img[i][j]));
			j++;
		}
		i++;
	}
	return (tex);
}
