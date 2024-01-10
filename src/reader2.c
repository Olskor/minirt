/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbourgue <fbourgue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 11:40:57 by fbourgue          #+#    #+#             */
/*   Updated: 2024/01/10 11:42:57 by fbourgue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void		error_parse(char *msg);
void		set_resolution(char **line, t_data *data);
t_cam		*cr_camera(char	**line);

void	_valide_res(t_data *data, char **line)
{
	if (data && data->b_no_more_res)
		error_parse ("La résolution a déjà été définie.");
	set_resolution (&*line, data);
	data->b_no_more_res = 1;
}

void	_valide_cam(t_data *data, char **line)
{
	if (data && data->cam)
		error_parse ("Une caméra est déja configurée");
	data->cam = cr_camera (&*line);
}

void	_valide_light(t_data *data, char **line)
{
	if (data && data->light && data->b_no_more_light)
		error_parse ("Une source lumineuse  est déja configurée");
	_add_light (cr_light (&*line, data), data);
	data->b_no_more_light = 1;
}

char	*_valide_ambiant(t_data *data, char *line)
{
	if (data->ambient)
		error_parse ("Une Ambient est déja configurée");
	data->ambient = cr_ambient (&line, data);
	return (line);
}

void	_syntax_error(char *line)
{
	char	*err;

	if (*line)
	{
		err = ft_strjoin ("Problème de syntaxe :\n", line);
		error_parse (err);
		free (err);
	}
}
