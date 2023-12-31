/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olskor <olskor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 14:41:39 by olskor            #+#    #+#             */
/*   Updated: 2023/12/31 17:49:51 by olskor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_sphere	*cr_sphere(char	**line);
t_cam	*cr_camera(char	**line);
t_plane	*cr_plane(char	**line);
t_cylinder	*cr_cylinder(char	**line);

/*int	_tab_size(void *t, int struct_size)
{
	int	nb;
	void	*pt;

	pt = t;
	nb = 0;
	while(pt && *(int*)pt)
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
	int	nb;

	pt_data = data->cylinder;
	nb = _tab_size(data->cylinder, sizeof(t_cylinder));
	tab = calloc(sizeof(t_cylinder),  (nb +2));
	pt_tab = tab;
	while (pt_data && *pt_data)
		*(pt_tab++) =* (pt_data++);
	*(pt_tab++) = s;
//	*pt_tab = NULL;
	tab[nb + 1] = NULL;
	free (data->cylinder);
	data->cylinder = tab;
}
void	_add_plane(t_plane*s, t_data *data)
{
	t_plane	**tab;
	t_plane	**pt_tab;
	t_plane	**pt_data;
	int	nb;

	pt_data = data->plane;
	nb = _tab_size(data->plane, sizeof(t_plane));
	tab = calloc(sizeof(t_plane),  (nb +2));
	pt_tab = tab;
	while (pt_data && *pt_data)
		*(pt_tab++) =* (pt_data++);
	*(pt_tab++) = s;
//	*pt_tab = NULL;
	tab[nb + 1] = NULL;
	free (data->plane);
	data->plane = tab;
}

void	_add_sphere(t_sphere *s, t_data *data)
{
	t_sphere	**tab;
	t_sphere	**pt_tab;
	t_sphere	**pt_data;
	int	nb;

	pt_data = data->sphere;
	nb = _tab_size(data->sphere, sizeof(t_sphere));
	tab = calloc(sizeof(t_sphere),  (nb +2));
	pt_tab = tab;
	while (pt_data && *pt_data)
		*(pt_tab++) =* (pt_data++);
	*(pt_tab++) = s;
//	*pt_tab = NULL;
	tab[nb + 1] = NULL;
	free (data->sphere);
	data->sphere = tab;
}*/

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
		if (ft_strnstr(line, "pl", 2))
		{
			_add_plane(cr_plane(&line), data);
		}
		else if (ft_strnstr(line, "cy", 2))
		{
			_add_cylinder(cr_cylinder(&line), data);
		}
		else if (ft_strnstr(line, "sp", 2))
		{
			_add_sphere(cr_sphere(&line), data);
		}
		else if (ft_strnstr(line, "c", 1))
		{
			if (data->cam)
				perror("Error\nUne caméra est déja configurée");
			data->cam = cr_camera(&line);
		}
		else if (ft_strnstr(line, "l", 1))
			_add_light(cr_light(&line), data);
		else if (ft_strnstr(line, "A", 1))
		{
			if (data->ambient)
				perror("Error\nUne Ambient est déja configurée");
			data->ambient = cr_ambient(&line);
		}
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
	data->box = NULL;
	printf("load\n");
	load(path, data);
}
