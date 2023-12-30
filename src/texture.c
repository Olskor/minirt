/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olskor <olskor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 11:58:23 by olskor            #+#    #+#             */
/*   Updated: 2023/12/30 13:27:46 by olskor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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
	int		i;

	img.mlx_img = mlx_xpm_file_to_image(data->mlx, path, &img.wi, &img.he);
	if (!img.mlx_img || img.wi != img.he)
		return (NULL);
	img.addr = mlx_get_data_addr(img.mlx_img, &img.bpp,
			&img.line_len, &img.endian);
	i = -1;
	tex = malloc(sizeof(t_Tex));
	tex->img = malloc(sizeof(t_Col *) * img.wi);
	tex->res = img.wi;
	while (i++ < img.wi)
	{
		tex->img[i] = malloc(sizeof(t_Col) * img.wi);
		img.he = 0;
		while (img.he < img.wi)
		{
			tex->img[i][img.he] = trgb_to_col(img_pix_read(&img, i, img.he));
			img.he++;
		}
	}
	free(img.mlx_img);
	return (tex);
}
