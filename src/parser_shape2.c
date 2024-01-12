/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_shape2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbourgue <fbourgue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 16:37:06 by fbourgue          #+#    #+#             */
/*   Updated: 2024/01/12 16:37:34 by fbourgue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

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
	*ret = read_obj(next(line), d, 1);
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
