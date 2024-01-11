/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olskor <olskor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 14:41:39 by olskor            #+#    #+#             */
/*   Updated: 2024/01/11 15:00:59 by olskor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_sphere	*cr_sphere(char	**line);
t_plane		*cr_plane(char	**line);
t_cylinder	*cr_cylinder(char	**line);
t_cube		*cr_cube(char	**line, t_data	*d);
void		on_spaces(char **s_init);
char		*_comment(int fd, char *sline, char **line);
void		_valide_res(t_data *data, char **line);
void		_valide_cam(t_data *data, char **line);
void		_valide_light(t_data *data, char **line);
char		*_valide_ambiant(t_data *data, char *line);
void		_syntax_error(char *line);
void		_add_cube(t_cube *s, t_data *data);

void	_parse_line(char **line, t_data *data)
{
	if (ft_strnstr (*line, "pl", 2))
		_add_plane (cr_plane (&*line), data);
	else if (ft_strnstr (*line, "cy", 2))
		_add_cylinder (cr_cylinder (&*line), data);
	else if (ft_strnstr (*line, "sp", 2))
		_add_sphere (cr_sphere (&*line), data);
	else if (ft_strnstr (*line, "sq", 2))
		_add_cube(cr_cube (&*line, data), data);
	else if (ft_strnstr (*line, "R", 1))
		_valide_res (data, &*line);
	else if (ft_strnstr (*line, "c", 1))
		_valide_cam (data, &*line);
	else if (ft_strnstr (*line, "L", 1))
		_valide_light (data, &*line);
	else if (ft_strnstr (*line, "l", 1))
		_add_light (cr_light (&*line, data), data);
	else if (ft_strnstr (*line, "A", 1))
		*line = _valide_ambiant (data, *line);
	else
		_syntax_error (*line);
}

void	load(char	*path, t_data *data)
{
	int		fd;
	char	*line;
	char	*sline;

	fd = open(path, O_RDONLY);
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
		if (data->b_parse_error)
			break ;
		free (sline);
		line = get_next_line(fd);
		sline = line;
	}
	close(fd);
	free (sline);
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
	data->cube = NULL;
	data->cam = NULL;
	data->b_no_more_light = 0;
	data->b_parse_error = 0;
	data->b_no_more_res = 0;
	load(path, data);
}
