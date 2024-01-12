/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbourgue <fbourgue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 14:41:39 by olskor            #+#    #+#             */
/*   Updated: 2024/01/12 16:43:01 by fbourgue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	_parse_line(char **line, t_data *data)
{
	if (ft_strnstr (*line, "pl", 2))
		_add_plane (cr_plane (&*line, data), data);
	else if (ft_strnstr (*line, "cy", 2))
		_add_cylinder (cr_cylinder (&*line, data), data);
	else if (ft_strnstr (*line, "sp", 2))
		_add_sphere (cr_sphere (&*line, data), data);
	else if (ft_strnstr (*line, "sq", 2))
		_add_mesh(cr_cube (&*line, data), data);
	else if (ft_strnstr (*line, "tr", 2))
		_add_mesh(cr_tria (&*line, data), data);
	else if (ft_strnstr (*line, "ms", 2))
		_add_mesh(cr_mesh (&*line, data), data);
	else if (ft_strnstr (*line, "R", 1))
		_valide_res (data, &*line);
	else if (ft_strnstr (*line, "C", 1))
		_valide_cam (data, &*line);
	else if (ft_strnstr (*line, "L", 1))
		_valide_light (data, &*line);
	else if (ft_strnstr (*line, "l", 1))
		_add_light (cr_light (&*line, data), data);
	else if (ft_strnstr (*line, "A", 1))
		*line = _valide_ambiant (data, *line);
	else
		_syntax_error (*line, data);
	_valid_extra_line(line, data);
}

void	load(char	*path, t_data *data)
{
	int		fd;
	char	*line;
	char	*sline;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		_config_error("Le fichier passé en argument est introuvable.", data);
	line = get_next_line(fd);
	sline = line;
	while (line)
	{
		on_spaces(&line);
		if (ft_strnstr(line, "#", 1))
		{
			sline = _comment (fd, sline, &line);
			continue ;
		}
		_parse_line (&line, data);
		free (sline);
		line = get_next_line(fd);
		sline = line;
	}
	close(fd);
	free (sline);
}

void	valide_config(t_data *data)
{
	if (! data->ambient)
		_config_error("Il n'y a aucun Ambiant", data);
	if (! data->ambient)
		_config_error("Il n'y a aucun Ambiant", data);
}

void	create_config(char *path, t_data *data)
{
	data->frame = 0;
	data->rand = 0;
	data->sample = 0;
	data->sky.active = 0;
	data->ambient = NULL;
	data->cylinder = NULL;
	data->plane = NULL;
	data->sphere = NULL;
	data->light = NULL;
	data->mesh = NULL;
	data->cam = NULL;
	data->cimg = NULL;
	data->b_no_more_light = 0;
	data->b_parse_error = 0;
	data->b_no_more_res = 0;
	load(path, data);
}
