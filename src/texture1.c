/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olskor <olskor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 15:20:14 by olskor            #+#    #+#             */
/*   Updated: 2024/01/11 15:57:02 by olskor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	create_planetexture(t_data *data)
{
	t_plane	**plane;

	plane = data->plane;
	while (plane && *plane)
	{
		if ((*plane)->mat.texpath)
			(*plane)->mat.tex = load_img((*plane)->mat.texpath, data);
		else
			(*plane)->mat.tex = NULL;
		if ((*plane)->mat.bumpath)
			(*plane)->mat.bump = load_img((*plane)->mat.bumpath, data);
		else
			(*plane)->mat.bump = NULL;
		if ((*plane)->mat.pbrpath)
			(*plane)->mat.pbr = load_img((*plane)->mat.pbrpath, data);
		else
			(*plane)->mat.pbr = NULL;
		free((*plane)->mat.texpath);
		free((*plane)->mat.bumpath);
		free((*plane)->mat.pbrpath);
		plane++;
	}
}

void	create_spheretexture(t_data *data)
{
	t_sphere	**sphere;

	sphere = data->sphere;
	while (sphere && *sphere)
	{
		if ((*sphere)->mat.texpath)
			(*sphere)->mat.tex = load_img((*sphere)->mat.texpath, data);
		else
			(*sphere)->mat.tex = NULL;
		if ((*sphere)->mat.bumpath)
			(*sphere)->mat.bump = load_img((*sphere)->mat.bumpath, data);
		else
			(*sphere)->mat.bump = NULL;
		if ((*sphere)->mat.pbrpath)
			(*sphere)->mat.pbr = load_img((*sphere)->mat.pbrpath, data);
		else
			(*sphere)->mat.pbr = NULL;
		free((*sphere)->mat.texpath);
		free((*sphere)->mat.bumpath);
		free((*sphere)->mat.pbrpath);
		sphere++;
	}
}

void	create_texture(t_data *data)
{
	create_planetexture(data);
	create_spheretexture(data);
}
