/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   factory_shape.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbourgue <fbourgue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 16:39:22 by fbourgue          #+#    #+#             */
/*   Updated: 2024/01/12 16:34:13 by fbourgue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int	_tab_size(void *t, int struct_size)
{
	int		nb;
	void	*pt;

	pt = t;
	nb = 0;
	while (pt && *(int *)pt)
	{
		nb++;
		pt += struct_size;
	}
	return (nb);
}

void	_add_cylinder(t_cylinder*s, t_data *data)
{
	t_cylinder	**tab;
	t_cylinder	**pt_tab;
	t_cylinder	**pt_data;
	int			nb;

	pt_data = data->cylinder;
	nb = _tab_size(data->cylinder, sizeof(t_cylinder *));
	tab = calloc(sizeof(t_cylinder *), (nb +2));
	pt_tab = tab;
	while (pt_data && *pt_data)
		*(pt_tab++) = *(pt_data++);
	*(pt_tab++) = s;
	tab[nb + 1] = NULL;
	free (data->cylinder);
	data->cylinder = tab;
}

void	_add_plane(t_plane*s, t_data *data)
{
	t_plane	**tab;
	t_plane	**pt_tab;
	t_plane	**pt_data;
	int		nb;

	pt_data = data->plane;
	nb = _tab_size(data->plane, sizeof(t_plane *));
	tab = calloc(sizeof(t_plane *), (nb + 2));
	pt_tab = tab;
	while (pt_data && *pt_data)
		*(pt_tab++) = *(pt_data++);
	*(pt_tab++) = s;
	tab[nb + 1] = NULL;
	free (data->plane);
	data->plane = tab;
}

void	_add_sphere(t_sphere *s, t_data *data)
{
	t_sphere	**tab;
	t_sphere	**pt_tab;
	t_sphere	**pt_data;
	int			nb;

	pt_data = data->sphere;
	nb = _tab_size(data->sphere, sizeof(t_sphere *));
	tab = calloc(sizeof(t_sphere *), (nb +2));
	pt_tab = tab;
	while (pt_data && *pt_data)
		*(pt_tab++) = *(pt_data++);
	*(pt_tab++) = s;
	tab[nb + 1] = NULL;
	free (data->sphere);
	data->sphere = tab;
}

void	_add_sky(t_sky c, t_data *data)
{
	data->sky = c;
}
