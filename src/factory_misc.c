/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   factory_misc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbourgue <fbourgue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 16:26:20 by fbourgue          #+#    #+#             */
/*   Updated: 2023/12/30 00:31:16 by fbourgue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int	_tab_size(void *t, int struct_size);

void	_add_ambient(t_Col c, t_data *data)
{
	data->ambient = c;
}

void	_add_light(t_light *s, t_data *data)
{
	t_light	**tab;
	t_light	**pt_tab;
	t_light	**pt_data;
	int		nb;

	pt_data = data->light;
	nb = _tab_size(data->light, sizeof(t_light));
	tab = calloc(sizeof(t_light), (nb +2));
	pt_tab = tab;
	while (pt_data && *pt_data)
		*(pt_tab++) =* (pt_data++);
	*(pt_tab++) = s;
	tab[nb + 1] = NULL;
	free (data->light);
	data->light = tab;
}
