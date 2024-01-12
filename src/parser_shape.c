/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_shape.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olskor <olskor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 16:29:21 by fbourgue          #+#    #+#             */
/*   Updated: 2024/01/12 12:40:48 by olskor           ###   ########.fr       */
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
	ret->dir =unit_vec3(_valide_vect_norm(ret->dir, d));
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

t_mesh	*cr_cube(char	**line, t_data	*d)
{
	t_mesh	*ret;
	float	size;

	(*line) += 2;
	ret = malloc(sizeof(t_mesh));
	*ret = read_obj("box.obj", d);
	_grab_3_doubles(&ret->pos, line, d);
	_grab_3_doubles(&ret->dir, line, d);
	ret->dir = unit_vec3(_valide_vect_norm(ret->dir, d));
	ret->up = unit_vec3(_valide_vect_norm(cross(ret->dir, vec3(0, 1, 0)), d));
	size = _valide_positif((_double(next(line), d) / 2),
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

t_mesh	*cr_tria(char **line, t_data *d)
{
	t_mesh	*ret;

	(*line) += 2;
	ret = malloc(sizeof(t_mesh));
	ret->tri = malloc(sizeof(t_Tri) * 2);
	_grab_3_doubles(&ret->tri[0].pos1, line, d);
	_grab_3_doubles(&ret->tri[0].pos2, line, d);
	_grab_3_doubles(&ret->tri[0].pos3, line, d);
	ret->tri[1].pos1 = ret->tri[0].pos1;
	ret->tri[1].pos3 = ret->tri[0].pos2;
	ret->tri[1].pos2 = ret->tri[0].pos3;
	ret->tri->mesh = ret;
	ret->trinbr = 2;
	_grab_col(&ret->mat.col, line, d);
	ret->mat.smooth = _double_fail_back(line, 0.0, d);
	ret->mat.metal = _double_fail_back(line, 0.0, d);
	ret->mat.tex = 0;
	ret->mat.bump = 0;
	ret->mat.pbr = 0;
	ret->mat.col.t = 0;
	ret->box = calculate_box(*ret);
	return (ret);
}

t_mesh	*cr_mesh(char **line, t_data *d)
{
	t_mesh	*ret;
	float	size;

	(*line) += 2;
	ret = malloc(sizeof(t_mesh));
	*ret = read_obj(next(line), d);
	_grab_3_doubles(&ret->pos, line, d);
	_grab_3_doubles(&ret->dir, line, d);
	_grab_3_doubles(&ret->up, line, d);
	ret->dir = unit_vec3(ret->dir);
	ret->up = unit_vec3(cross(ret->dir, ret->up));
	size = _valide_positif((_double(next(line), d) / 2),
			"La taille d'un mesh ", d);
	ret->scale = vec3(size, size, size);
	_grab_col(&ret->mat.col, line, d);
	ret->mat.smooth = _double_fail_back(line, 0.0, d);
	ret->mat.metal = _double_fail_back(line, 0.0, d);
	ret->mat.tex = 0;
	ret->mat.bump = 0;
	ret->mat.pbr = 0;
	*ret = rotate_mesh(*ret);
	*ret = scale_mesh(*ret);
	*ret = translate_mesh(*ret);
	ret->box = calculate_box(*ret);
	return (ret);
}
