/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olskor <olskor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 19:02:20 by olskor            #+#    #+#             */
/*   Updated: 2023/12/29 16:47:30 by olskor           ###   ########.fr       */
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

t_box_tri	calculate_box(t_mesh mesh)
{
	t_box_tri	box;
	int			i;

	i = 0;
	box.min = mesh.tri[0].pos1;
	box.max = mesh.tri[0].pos1;
	while (i < mesh.trinbr)
	{
		if (box.min.x > mesh.tri[i].pos1.x)
			box.min.x = mesh.tri[i].pos1.x;
		if (box.min.y > mesh.tri[i].pos1.y)
			box.min.y = mesh.tri[i].pos1.y;
		if (box.min.z > mesh.tri[i].pos1.z)
			box.min.z = mesh.tri[i].pos1.z;
		if (box.max.x < mesh.tri[i].pos1.x)
			box.max.x = mesh.tri[i].pos1.x;
		if (box.max.y < mesh.tri[i].pos1.y)
			box.max.y = mesh.tri[i].pos1.y;
		if (box.max.z < mesh.tri[i].pos1.z)
			box.max.z = mesh.tri[i].pos1.z;
		if (box.min.x > mesh.tri[i].pos2.x)
			box.min.x = mesh.tri[i].pos2.x;
		if (box.min.y > mesh.tri[i].pos2.y)
			box.min.y = mesh.tri[i].pos2.y;
		if (box.min.z > mesh.tri[i].pos2.z)
			box.min.z = mesh.tri[i].pos2.z;
		if (box.max.x < mesh.tri[i].pos2.x)
			box.max.x = mesh.tri[i].pos2.x;
		if (box.max.y < mesh.tri[i].pos2.y)
			box.max.y = mesh.tri[i].pos2.y;
		if (box.max.z < mesh.tri[i].pos2.z)
			box.max.z = mesh.tri[i].pos2.z;
		if (box.min.x > mesh.tri[i].pos3.x)
			box.min.x = mesh.tri[i].pos3.x;
		if (box.min.y > mesh.tri[i].pos3.y)
			box.min.y = mesh.tri[i].pos3.y;
		if (box.min.z > mesh.tri[i].pos3.z)
			box.min.z = mesh.tri[i].pos3.z;
		if (box.max.x < mesh.tri[i].pos3.x)
			box.max.x = mesh.tri[i].pos3.x;
		if (box.max.y < mesh.tri[i].pos3.y)
			box.max.y = mesh.tri[i].pos3.y;
		if (box.max.z < mesh.tri[i].pos3.z)
			box.max.z = mesh.tri[i].pos3.z;
		i++;
	}
	return (box);
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
	int	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

t_Vec3	*ft_append_pos(t_Vec3 *pos, t_Vec3 newpos, int i)
{
	t_Vec3	*new;
	int		j;

	if (i)
	{
		new = malloc(sizeof(t_Vec3) * (i + 1));
		j = 0;
		while (j < i)
		{
			new[j] = pos[j];
			j++;
		}
		new[j] = newpos;
		free(pos);
		return (new);
	}
	new = malloc(sizeof(t_Vec3) * (i + 1));
	new[0] = newpos;
	return (new);
}
t_Tri	*ft_append_tri(t_Tri *tri, t_Tri newtri, int i)
{
	t_Tri	*new;
	int		j;

	if (i)
	{
		new = malloc(sizeof(t_Tri) * (i + 1));
		j = 0;
		while (j < i)
		{
			new[j] = tri[j];
			j++;
		}
		new[j] = newtri;
		free(tri);
		return (new);
	}
	new = malloc(sizeof(t_Tri) * (i + 1));
	new[0] = newtri;
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
	pos = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (line[0] == 'v' && line[1] == ' ')
		{
			split = ft_split(line, ' ');
			if (split[1] && split[2] && split[3])
			{
				pos = ft_append_pos(pos, vec3(ft_atof(split[1]), ft_atof(split[2]), ft_atof(split[3])), i);
				i++;
			}
			free_split(split);
		}
		if (line[0] == 'f' && line[1] == ' ')
		{
			split = ft_split(line, ' ');
			if (split[1] && split[2] && split[3])
			{
				mesh.tri = ft_append_tri(mesh.tri, create_triangle(pos[ft_atoi(split[1]) - 1], pos[ft_atoi(split[2]) - 1], pos[ft_atoi(split[3]) - 1]), j);
				j++;
			}
			free_split(split);
		}
		free(line);
		line = get_next_line(fd);
	}
	mesh.trinbr = j;
	if (pos)
		free(pos);
	close(fd);
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

t_mesh	rotate_mesh(t_mesh mesh)
{
	int		i;

	i = 0;
	while (i < mesh.trinbr)
	{
		mesh.tri[i].pos1 = rotatevec3(mesh.tri[i].pos1, mesh.dir, mesh.up);
		mesh.tri[i].pos2 = rotatevec3(mesh.tri[i].pos2, mesh.dir, mesh.up);
		mesh.tri[i].pos3 = rotatevec3(mesh.tri[i].pos3, mesh.dir, mesh.up);
		i++;
	}
	return (mesh);
}

t_mesh	scale_mesh(t_mesh mesh)
{
	int		i;

	i = 0;
	while (i < mesh.trinbr)
	{
		mesh.tri[i].pos1 = mulvec3(mesh.tri[i].pos1, mesh.scale);
		mesh.tri[i].pos2 = mulvec3(mesh.tri[i].pos2, mesh.scale);
		mesh.tri[i].pos3 = mulvec3(mesh.tri[i].pos3, mesh.scale);
		i++;
	}
	return (mesh);
}
