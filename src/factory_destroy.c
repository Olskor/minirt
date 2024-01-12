/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   factory_destroy.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olskor <olskor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 00:30:27 by fbourgue          #+#    #+#             */
/*   Updated: 2024/01/12 11:43:56 by olskor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	free_texture(t_data *data);

void	_kill_pointer_tab(void **t)
{
	while (t && *t)
	{
		free(*t);
		t++;
	}
}

void	_free_mesh(t_mesh **mesh)
{
	while (mesh && *mesh)
	{
		free((*mesh)->tri);
		free(*mesh);
		mesh++;
	}
}

void	cleanup(t_data	*d)
{
	free_texture(d);
	_kill_pointer_tab((void **)d->cylinder);
	_kill_pointer_tab((void **)d->plane);
	_kill_pointer_tab((void **)d->sphere);
	_kill_pointer_tab((void **)d->light);
	_kill_pointer_tab((void **)d->cimg);
	_free_mesh(d->mesh);
	free(d->cam);
	free (d->cylinder);
	free (d->sphere);
	free (d->plane);
	free (d->ambient);
	free(d->light);
	free(d->cimg);
	free(d->mesh);
	free(d);
}
