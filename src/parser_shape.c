/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_shape.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbourgue <fbourgue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 16:29:21 by fbourgue          #+#    #+#             */
/*   Updated: 2024/01/12 16:37:29 by fbourgue         ###   ########.fr       */
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
	unit_vec3(_valide_vect_norm(ret->norm, d));
	_grab_col(&ret->mat.col, line, d);
	ret->mat.smooth = _double_fail_back(line, 0.0, d);
	ret->mat.metal = _double_fail_back(line, 0.0, d);
	ret->mat.tex = 0;
	ret->mat.texpath = _text_fail_back(line);
	ret->mat.bump = 0;
	ret->mat.bumpath = _text_fail_back(line);
	ret->mat.pbr = 0;
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
	ret->dir = unit_vec3(_valide_vect_norm(ret->dir, d));
	ret->rad = _valide_positif_non_nul((_double(next(line), d) / 2),
			"le rayon d'un cylindre", d);
	ret->h = _valide_positif_non_nul(_double(next(line), d),
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
	ret->rad = _valide_positif_non_nul((_double(next(line), d) / 2),
			"le rayon d'une sphère ", d);
	_grab_col(&ret->mat.col, line, d);
	ret->mat.smooth = _double_fail_back(line, 0.0, d);
	ret->mat.metal = _double_fail_back(line, 0.0, d);
	ret->mat.tex = 0;
	ret->mat.texpath = _text_fail_back(line);
	ret->mat.bump = 0;
	ret->mat.bumpath = _text_fail_back(line);
	ret->mat.pbr = 0;
	ret->mat.pbrpath = _text_fail_back(line);
	ret->mat.col.t = 0;
	return (ret);
}

t_mesh	*cr_cube(char	**line, t_data	*d)
{
	t_mesh	*ret;
	float	size;

	(*line) += 2;
	ret = malloc(sizeof(t_mesh));
	*ret = read_obj("mesh/box.obj", d, 0);
	_grab_3_doubles(&ret->pos, line, d);
	_grab_3_doubles(&ret->dir, line, d);
	ret->dir = unit_vec3(_valide_vect_norm(ret->dir, d));
	ret->up = unit_vec3(_valide_vect_norm(cross(ret->dir, vec3(0, 1, 0)), d));
	size = _valide_positif_non_nul((_double(next(line), d) / 2),
			"La longueur du côté d'un cube ", d);
	ret->scale = vec3(size, size, size);
	_grab_col(&ret->mat.col, line, d);
	ret->mat.smooth = _double_fail_back(line, 0.0, d);
	ret->mat.metal = _double_fail_back(line, 0.0, d);
	ret->mat.tex = 0;
	ret->mat.bump = 0;
	ret->mat.pbr = 0;
	ret->mat.col.t = 0;
	*ret = rotate_mesh(*ret);
	*ret = scale_mesh(*ret);
	*ret = translate_mesh(*ret);
	ret->box = calculate_box(*ret);
	return (ret);
}
