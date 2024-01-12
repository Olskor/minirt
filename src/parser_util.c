/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbourgue <fbourgue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 23:27:20 by fbourgue          #+#    #+#             */
/*   Updated: 2024/01/10 11:22:06 by fbourgue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	set_resolution(char **line, t_data *data)
{
	double	w;
	double	h;

	(*line) += 1;
	on_spaces(line);
	w = _double(next(line), data);
	h = _double(next(line), data);
	data->wi = w;
	data->he = h;
}

t_Col	scalecol_parser(t_Col col1, double sampleperpixel)
{
	col1.t = col1.t * sampleperpixel;
	col1.r = col1.r * sampleperpixel;
	col1.g = col1.g * sampleperpixel;
	col1.b = col1.b * sampleperpixel;
	return (col1);
}

void	error_parse(char *msg, t_data	*data)
{
	if (msg)
		printf("Error\n%s\n", msg);
	else
		printf("Error\n");
	data->b_parse_error = 1;
}

int	ft_atoi_free_param(char *str)
{
	int	ret;

	ret = ft_atoi(str);
	free(str);
	return (ret);
}

void	_valide_col(t_Vec3 c, t_data	*d)
{
	if (c.x < 0 || c.y < 0 || c.z < 0)
		error_parse("Valeur négative interdite pour une couleur", d);
	if (c.x > 255 || c.y > 255 || c.z > 255)
		error_parse("Valeur > 255 interdite pour une couleur", d);
}
