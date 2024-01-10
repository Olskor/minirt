/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   factory_shape2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbourgue <fbourgue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 12:13:07 by fbourgue          #+#    #+#             */
/*   Updated: 2024/01/10 12:13:13 by fbourgue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	_tab_size(void *t, int struct_size);

void	_add_cube(t_cube *s, t_data *data)
{
	t_cube	**tab;
	t_cube	**pt_tab;
	t_cube	**pt_data;
	int		nb;

	pt_data = data->cube;
	nb = _tab_size(data->cube, sizeof(t_cube *));
	tab = calloc(sizeof(t_cube *), (nb +2));
	pt_tab = tab;
	while (pt_data && *pt_data)
		*(pt_tab++) = *(pt_data++);
	*(pt_tab++) = s;
	tab[nb + 1] = NULL;
	free (data->cube);
	data->cube = tab;
}
