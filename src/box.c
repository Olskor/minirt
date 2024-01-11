/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   box.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olskor <olskor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 16:09:21 by olskor            #+#    #+#             */
/*   Updated: 2024/01/11 13:23:33 by olskor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	create_cube2(t_data *data, int i, t_cube *cube)
{
	data->mesh[i] = (t_mesh *)malloc(sizeof(t_mesh));
	*data->mesh[i] = read_obj("box.obj");
	data->mesh[i]->pos = cube->pos;
	data->mesh[i]->mat = cube->mat;
	data->mesh[i]->dir = unit_vec3(vec3(cube->dir.x, cube->dir.y, cube->dir.z));
	data->mesh[i]->up = unit_vec3(cross(data->mesh[i]->dir, vec3(0, 1, 0)));
	data->mesh[i]->scale = vec3(cube->size, cube->size, cube->size);
	*data->mesh[i] = rotate_mesh(*data->mesh[0]);
	*data->mesh[i] = scale_mesh(*data->mesh[0]);
	*data->mesh[i] = translate_mesh(*data->mesh[0]);
	data->mesh[i]->box = calculate_box(*data->mesh[0]);
}

void	create_cube(t_data *data)
{
	t_cube	**cube;
	int		i;

	cube = data->cube;
	i = 0;
	while (cube && *cube)
		cube = cube + 1 + (i++ *0);
	if (i == 0)
		return ;
	data->mesh = (t_mesh **)malloc(sizeof(t_mesh *) * (i + 1));
	cube = data->cube;
	i = 0;
	while (cube && *cube)
	{
		create_cube2(data, i, *cube);
		cube = cube + 1 + (i++ *0);
	}
	data->mesh[i] = 0;
}
