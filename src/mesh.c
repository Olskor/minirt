/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olskor <olskor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 19:02:20 by olskor            #+#    #+#             */
/*   Updated: 2023/12/23 01:13:23 by olskor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_Tri	create_triangle(t_Vec3 pos1, t_Vec3 pos2, t_Vec3 pos3)
{
	t_Tri	triangle;

	triangle.pos1 = pos1;
	triangle.pos2 = pos2;
	triangle.pos3 = pos3;
	return (triangle);
}

float	ft_atof(char *str)
{
	float result = 0.0;
	float sign = 1.0;
	int i = 0;

	if (str[i] == '-')
	{
		sign = -1.0;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10.0 + (str[i] - '0');
		i++;
	}
	if (str[i] == '.')
	{
		float factor = 0.1;
		i++;

		while (str[i] >= '0' && str[i] <= '9')
		{
			result += (str[i] - '0') * factor;
			factor *= 0.1;
			i++;
		}
	}
	return result * sign;
}

void	free_split(char **split)
{
	int i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

t_Vec3	*append_pos(t_Vec3 *pos, t_Vec3 newpos, int i)
{
	t_Vec3	*new;
	int		j;

	new = malloc(sizeof(t_Vec3) * (i + 1));
	while (j < i)
	{
		new[j] = pos[j];
		j++;
	}
	new[j] = newpos;
	free(pos);
	return (new);
}

t_mesh	read_obj(char *obj)
{
	t_mesh	mesh;
	t_Vec3	*pos;
	int		fd;
	char	*line;
	char	**split;
	int		i;
	int		j;

	i = 0;
	j = 0;
	fd = open(obj, O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		if (line[0] == 'v' && line[1] == ' ')
		{
			split = ft_split(line, ' ');
			if (split[1] && split[2] && split[3])
			{
				pos = realloc(pos, sizeof(t_Vec3) * (i + 1));
				pos[i] = vec3(ft_atof(split[1]), ft_atof(split[2]), ft_atof(split[3]));
				i++;
			}
			free_split(split);
		}
		if (line[0] == 'f' && line[1] == ' ')
		{
			split = ft_split(line, ' ');
			if (split[1] && split[2] && split[3])
			{
				mesh.tri = realloc(mesh.tri, sizeof(t_Tri) * (j + 1));
				mesh.tri[j].pos1 = pos[ft_atoi(split[1]) - 1];
				mesh.tri[j].pos2 = pos[ft_atoi(split[2]) - 1];
				mesh.tri[j].pos3 = pos[ft_atoi(split[3]) - 1];
				j++;
			}
			free_split(split);
		}
		free(line);
		line = get_next_line(fd);
	}
	mesh.trinbr = j;
	free(pos);
	return (mesh);
}

t_mesh	create_cube(void)
{
	t_mesh	mesh;

	mesh = read_obj("icosphere.obj");
	return (mesh);
}

t_mesh	translate_mesh(t_mesh mesh)
{
	int		i;

	i = 0;
	while (i < mesh.trinbr)
	{
		mesh.tri[i].pos1 = addvec3(mesh.tri[i].pos1, mesh.pos);
		mesh.tri[i].pos2 = addvec3(mesh.tri[i].pos2, mesh.pos);
		mesh.tri[i].pos3 = addvec3(mesh.tri[i].pos3, mesh.pos);
		i++;
	}
	return (mesh);
}