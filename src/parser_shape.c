/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_shape.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olskor <olskor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 16:29:21 by fbourgue          #+#    #+#             */
/*   Updated: 2024/01/11 16:04:06 by olskor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_plane	*cr_plane(char	**line, t_data	*d)
{
	t_plane	*ret;

	(*line) += 2;
	ret = malloc(sizeof(t_plane));
	_grab_3_doubles(&ret->pos, line, d);
	_grab_3_doubles(&ret->norm, line, d);
	unit_vec3(ret->norm);
	_grab_col(&ret->mat.col, line, d);
	ret->mat.smooth = _double_fail_back(line, 0.0, d);
	ret->mat.metal = _double_fail_back(line, 0.0, d);
	ret->mat.texpath = _text_fail_back(line);
	ret->mat.bumpath = _text_fail_back(line);
	ret->mat.pbrpath = _text_fail_back(line);
	ret->mat.col.t = 0;
	return (ret);
}

t_sky	cr_sky(char	**line, t_data	*d)
{
	t_sky	ret;

	(*line) += 2;
	_grab_3_doubles(&ret.sun, line, d);
	ret.intensity = _double(next(line), d);
	return (ret);
}

t_cylinder	*cr_cylinder(char	**line, t_data	*d)
{
	t_cylinder	*ret;

	(*line) += 2;
	ret = malloc(sizeof(t_cylinder));
	_grab_3_doubles(&ret->pos, line, d);
	_grab_3_doubles(&ret->dir, line, d);
	ret->dir = unit_vec3(ret->dir);
	ret->rad = _valide_positif((_double(next(line), d) / 2),
			"le rayon d'un cylindre", d);
	ret->h = _valide_positif(_double(next(line), d),
			"la hauteur d'un cylindre", d);
	_grab_col(&ret->mat.col, line, d);
	ret->mat.tex = 0;
	ret->mat.bump = 0;
	ret->mat.pbr = 0;
	ret->mat.col.t = 0;
	ret->mat.smooth = _double_fail_back(line, 0.0, d);
	ret->mat.metal = _double_fail_back(line, 0.0, d);
	return (ret);
}

t_sphere	*cr_sphere(char	**line, t_data	*d)
{
	t_sphere	*ret;

	(*line) += 2;
	ret = malloc(sizeof(t_sphere));
	_grab_3_doubles(&ret->pos, line, d);
	ret->rad = _valide_positif((_double(next(line), d) / 2),
			"le rayon d'une sphère ", d);
	_grab_col(&ret->mat.col, line, d);
	ret->mat.smooth = _double_fail_back(line, 0.0, d);
	ret->mat.metal = _double_fail_back(line, 0.0, d);
	ret->mat.texpath = _text_fail_back(line);
	ret->mat.bumpath = _text_fail_back(line);
	ret->mat.pbrpath = _text_fail_back(line);
	ret->mat.col.t = 0;
	return (ret);
}

t_cube	*cr_cube(char	**line, t_data	*d)
{
	t_cube	*ret;

	(*line) += 2;
	ret = malloc(sizeof(t_cube));
	_grab_3_doubles(&ret->pos, line, d);
	_grab_3_doubles(&ret->dir, line, d);
	ret->size = _valide_positif((_double(next(line), d) / 2),
			"La longueur du côté d'un cube ", d);
	_grab_col(&ret->mat.col, line, d);
	ret->mat.tex = 0;
	ret->mat.bump = 0;
	ret->mat.pbr = 0;
	ret->mat.col.t = 0;
	ret->mat.smooth = _double_fail_back(line, 0.0, d);
	ret->mat.metal = _double_fail_back(line, 0.0, d);
	return (ret);
}
