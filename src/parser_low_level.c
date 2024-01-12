/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_low_level.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbourgue <fbourgue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 16:30:18 by fbourgue          #+#    #+#             */
/*   Updated: 2024/01/12 16:34:41 by fbourgue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

char	*next(char **line)
{
	char	*ret;
	char	*next_coma;
	char	*next_space;

	on_spaces(line);
	next_coma = ft_strchr(*line, ',');
	if (!next_coma)
		next_coma = ft_strchr(*line, '\n');
	next_space = ft_spacechr(*line);
	if (next_space == 0 || (next_coma && (next_coma < next_space)))
		ret = ft_substr(*line, 0, next_coma - *line);
	else
		ret = ft_substr(*line, 0, next_space - *line);
	if (ft_strlen(ret) > 0)
		*line += ft_strlen(ret) + 1;
	return (ret);
}

double	__conv_double(int i, double r, char *dot)
{
	double	deci;
	int		div;

	div = 1;
	while (--i > 0)
		div *= 10;
	deci = ft_atoi (++dot);
	if (r >= 0)
		r += (deci / div);
	else
		r -= (deci / div);
	return (r);
}

double	_double(char *params, t_data *d)
{
	float	r;

	(void) d;
	r = ft_atof(params);
	free(params);
	return (r);
}

double	_double_fail_back(char **params, double failBack, t_data *d)
{
	double	ret;

	if (params && *params && **params)
	{
		ret = _double(next(params), d);
		return (ret);
	}
	else
		return (failBack);
}

void	_grab_3_doubles(t_Vec3 *ret, char **line, t_data *d)
{
	double	t_double[3];

	t_double[0] = 0;
	t_double[1] = 0;
	t_double[2] = 0;
	t_double[0] = _double(next(line), d);
	t_double[1] = _double(next(line), d);
	t_double[2] = _double(next(line), d);
	*ret = (vec3(t_double[0], t_double[1], t_double[2]));
}
