/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olskor <olskor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 18:12:34 by olskor            #+#    #+#             */
/*   Updated: 2023/12/22 18:32:50 by olskor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	img_pix_put(t_img *img, int x, int y, int color)
{
	char	*pixel;
	int		i;

	if (x >= img->wi || y >= img->he)
		return ;
	if (x < 0 || y < 0)
		return ;
	i = img->bpp - 8;
	pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
	while (i >= 0)
	{
		if (img->endian != 0)
			*pixel++ = (color >> i) & 0xFF;
		else
			*pixel++ = (color >> (img->bpp - 8 - i)) & 0xFF;
		i -= 8;
	}
}

int	render_background(t_img *img, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < img->he)
	{
		j = 0;
		while (j < img->wi)
		{
			img_pix_put(img, j++, i, color);
		}
		++i;
	}
	return (0);
}

void	save_img(t_data *data)
{
	int		fd;
	int		i;
	int		j;
	char	*filename;
	char	*tmp;

	tmp = ft_itoa(data->frame);
	data->frame++;
	filename = ft_strjoin("img/", tmp);
	filename = ft_strjoin(filename, ".ppm");
	fd = open(filename, O_CREAT | O_WRONLY, 0666);
	write(fd, "P3\n", 3);
	free(tmp);
	tmp = ft_itoa(data->wi);
	write(fd, tmp, ft_strlen(tmp));
	write(fd, " ", 1);
	free(tmp);
	tmp = ft_itoa(data->he);
	write(fd, tmp, ft_strlen(tmp));
	write(fd, "\n", 1);
	i = 0;
	while (i < data->he)
	{
		j = 0;
		while (j < data->wi)
		{
			tmp = ft_itoa((int) (aces(data->cimg[i][j].b) * 255.99));
			write(fd, tmp, ft_strlen(tmp));
			write(fd, "\n", 1);
			free(tmp);
			tmp = ft_itoa((int) (aces(data->cimg[i][j].r) * 255.99));
			write(fd, tmp, ft_strlen(tmp));
			write(fd, "\n", 1);
			free(tmp);
			tmp = ft_itoa((int) (aces(data->cimg[i][j].g) * 255.99));
			write(fd, tmp, ft_strlen(tmp));
			write(fd, "\n", 1);
			free(tmp);
			j++;
		}
		i++;
	}
	free(filename);
	close(fd);
}
