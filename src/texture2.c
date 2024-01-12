/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olskor <olskor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 15:57:59 by olskor            #+#    #+#             */
/*   Updated: 2024/01/12 14:42:57 by olskor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	freetex(t_Tex *tex)
{
	int	i;

	i = 0;
	if (!tex)
		return ;
	while (i < tex->res)
	{
		free(tex->img[i]);
		i++;
	}
	free(tex->img);
	free(tex);
}

void	free_texture(t_data *data)
{
	t_plane		**plane;
	t_sphere	**sphere;

	plane = data->plane;
	while (plane && *plane)
	{
		freetex((*plane)->mat.tex);
		freetex((*plane)->mat.bump);
		freetex((*plane)->mat.pbr);
		plane++;
	}
	sphere = data->sphere;
	while (sphere && *sphere)
	{
		freetex((*sphere)->mat.tex);
		freetex((*sphere)->mat.bump);
		freetex((*sphere)->mat.pbr);
		sphere++;
	}
}
