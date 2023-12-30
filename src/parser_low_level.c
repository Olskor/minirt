/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_low_level.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbourgue <fbourgue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 16:30:18 by fbourgue          #+#    #+#             */
/*   Updated: 2023/12/30 00:35:47 by fbourgue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	on_spaces(char **s_init)
{
	char	*c;
	char	**s;

	s = s_init;
	while (s && *s && (
			**s == ' ' || **s == '\t' || **s == '\n'
		)
	)
	{
		(*s)++;
	}
}

char	*next(char **line)
{
	char	*ret;
	char	*next_coma;
	char	*next_space;

	on_spaces(line);
	next_coma = ft_strchr(*line, ',');
	next_space = ft_strchr(*line, ' ');
	if (next_space == 0 || (next_coma && (next_coma < next_space)))
		ret = ft_substr(*line, 0, next_coma - *line);
	else
		ret = ft_substr(*line, 0, next_space - *line);
	*line += ft_strlen(ret) + 1;
	return (ret);
}

double	_double(char *params)
{
	double	r;
	double	deci;
	char	*dot;
	int		div;
	int		i;

	div = 1;
	r = ft_atoi(params);
	dot = ft_strchr(params, '.');
	if (! dot)
	{
		free(params);
		return (r);
	}
	i = ft_strlen(dot);
	while (--i > 0)
		div *= 10;
	deci = ft_atoi(++dot);
	if (r >= 0)
		r += (deci / div);
	else
		r -= (deci / div);
	free(params);
	return (r);
}

double	_doubleFailBack(char **params, double failBack)
{
	double	ret;

	if (params && *params && **params && (ft_strlen(*params) > 0))
	{
		ret = _double(next(params));
		free (*params);
		return (ret);
	}
	else
		return (failBack);
}

void	_grab_3_doubles(t_Vec3 *ret, char **line)
{
	double	t_double[3];

	t_double[0] = 0;
	t_double[1] = 0;
	t_double[2] = 0;
	t_double[0] = _double(next(line));
	t_double[1] = _double(next(line));
	t_double[2] = _double(next(line));
	*ret = (vec3(t_double[0], t_double[1], t_double[2]));
}
