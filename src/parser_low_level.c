/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_low_level.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olskor <olskor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 16:30:18 by fbourgue          #+#    #+#             */
/*   Updated: 2024/01/11 15:03:16 by olskor           ###   ########.fr       */
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
	double	r;
	char	*dot;
	int		i;

	if (! (params && *params))
		error_parse(NULL, d);
	r = ft_atoi(params);
	dot = ft_strchr(params, '.');
	if (!dot)
	{
		free(params);
		return (r);
	}
	i = ft_strlen(dot);
	r = __conv_double (i, r, dot);
	free(params);
	return (r);
}

double	_double_fail_back(char **params, double failBack, t_data *d)
{
	double	ret;

	if (params && *params && **params && (ft_strlen(*params) > 0))
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
