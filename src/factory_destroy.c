/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   factory_destroy.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbourgue <fbourgue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 00:30:27 by fbourgue          #+#    #+#             */
/*   Updated: 2024/01/10 11:06:54 by fbourgue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	_kill_pointer_tab(void **t)
{
	while (t && *t)
	{
		free(*t);
		t++;
	}
}

void	cleanup(t_data	*d)
{
	_kill_pointer_tab((void **)d->cylinder);
	_kill_pointer_tab((void **)d->plane);
	_kill_pointer_tab((void **)d->sphere);
	_kill_pointer_tab((void **)d->light);
	_kill_pointer_tab((void **)d->cimg);
	_kill_pointer_tab((void **)d->cube);
	free(d->cam);
	free (d->cylinder);
	free (d->sphere);
	free (d->plane);
	free (d->ambient);
	free(d->light);
	free(d->cimg);
	free(d->cube);
	free(d);
}
