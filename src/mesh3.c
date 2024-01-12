/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olskor <olskor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 13:45:48 by olskor            #+#    #+#             */
/*   Updated: 2024/01/12 15:33:19 by olskor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_mesh	rotate_mesh(t_mesh mesh)
{
	int		i;

	i = 0;
	while (i < mesh.trinbr)
	{
		mesh.tri[i].pos1 = rotatevec3(mesh.tri[i].pos1, mesh.dir, mesh.up);
		mesh.tri[i].pos2 = rotatevec3(mesh.tri[i].pos2, mesh.dir, mesh.up);
		mesh.tri[i].pos3 = rotatevec3(mesh.tri[i].pos3, mesh.dir, mesh.up);
		i++;
	}
	return (mesh);
}

t_mesh	scale_mesh(t_mesh mesh)
{
	int		i;

	i = 0;
	while (i < mesh.trinbr)
	{
		mesh.tri[i].pos1 = mulvec3(mesh.tri[i].pos1, mesh.scale);
		mesh.tri[i].pos2 = mulvec3(mesh.tri[i].pos2, mesh.scale);
		mesh.tri[i].pos3 = mulvec3(mesh.tri[i].pos3, mesh.scale);
		i++;
	}
	return (mesh);
}

void	_test_free(void *ptr, int i)
{
	if (ptr != NULL && i == 1)
		free(ptr);
}

void	_mesh_init(t_mesh *mesh, t_Vec3 **pos, t_Int2 *ij)
{
	*ij = int2(0, 0);
	mesh->tri = NULL;
	*pos = NULL;
}
