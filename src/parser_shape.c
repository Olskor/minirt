/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_shape.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olskor <olskor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 16:29:21 by fbourgue          #+#    #+#             */
/*   Updated: 2023/12/31 16:14:50 by olskor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	on_spaces(char **s_init);
char	*next(char **line);
double	_double(char *params);
double	_doubleFailBack(char **params, double failBack);
void	_grab_3_doubles(t_Vec3 *ret, char **line);
void	_grab_col(t_Col *ret, char **line);

t_plane	*cr_plane(char	**line)
{
	t_plane	*ret;

	(*line) += 2;
	on_spaces(line);
	ret = malloc(sizeof(t_plane));
	_grab_3_doubles(&ret->pos, line);
	on_spaces(line);
	_grab_3_doubles(&ret->norm, line);
	unit_vec3(ret->norm);
	on_spaces(line);
	_grab_col(&ret->mat.col, line);
	ret->mat.tex = 0;
	ret->mat.bump = 0;
	ret->mat.pbr = 0;
	ret->mat.col.t = 0;
	on_spaces(line);
	ret->mat.smooth = _doubleFailBack(line, 0.0);
	on_spaces(line);
	ret->mat.metal = _doubleFailBack(line, 0.0);
	return (ret);
}

t_sky	cr_sky(char	**line)
{
	t_sky	ret;

	(*line) += 2;
	on_spaces(line);
	_grab_3_doubles(&ret.sun, line);
	on_spaces(line);
	ret.intensity = _double(next(line));
	return (ret);
}

t_cylinder	*cr_cylinder(char	**line)
{
	t_cylinder	*ret;

	(*line) += 2;
	on_spaces(line);
	ret = malloc(sizeof(t_cylinder));
	_grab_3_doubles(&ret->pos, line);
	on_spaces(line);
	_grab_3_doubles(&ret->dir, line);
	ret->dir = unit_vec3(ret->dir);
	on_spaces(line);
	ret->rad = (_double(next(line)) / 2);
	on_spaces(line);
	ret->h = (_double(next(line)));
	on_spaces(line);
	_grab_col(&ret->mat.col, line);
	ret->mat.tex = 0;
	ret->mat.bump = 0;
	ret->mat.pbr = 0;
	ret->mat.col.t = 0;
	on_spaces(line);
	ret->mat.smooth = _doubleFailBack(line, 0.0);
	on_spaces(line);
	ret->mat.metal = _doubleFailBack(line, 0.0);
	return (ret);
}

t_sphere	*cr_sphere(char	**line)
{
	t_sphere	*ret;

	(*line) += 2;
	on_spaces(line);
	ret = malloc(sizeof(t_sphere));
	_grab_3_doubles(&ret->pos, line);
	on_spaces(line);
	ret->rad = (_double(next(line)) / 2);
	on_spaces(line);
	_grab_col(&ret->mat.col, line);
	ret->mat.tex = 0;
	ret->mat.bump = 0;
	ret->mat.pbr = 0;
	ret->mat.col.t = 0;
	printf(*line);
	on_spaces(line);
	ret->mat.smooth = _doubleFailBack(line, 0.0);
	on_spaces(line);
	ret->mat.metal = _doubleFailBack(line, 0.0);
	return (ret);
}
