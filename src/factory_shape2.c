/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   factory_shape2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olskor <olskor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 12:13:07 by fbourgue          #+#    #+#             */
/*   Updated: 2024/01/12 11:42:38 by olskor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	_tab_size(void *t, int struct_size);

void	_add_mesh(t_mesh *s, t_data *data)
{
	t_mesh	**tab;
	t_mesh	**pt_tab;
	t_mesh	**pt_data;
	int		nb;

	pt_data = data->mesh;
	nb = _tab_size(data->mesh, sizeof(t_mesh *));
	tab = calloc(sizeof(t_mesh *), (nb +2));
	pt_tab = tab;
	while (pt_data && *pt_data)
		*(pt_tab++) = *(pt_data++);
	*(pt_tab++) = s;
	tab[nb + 1] = NULL;
	free (data->mesh);
	data->mesh = tab;
}
