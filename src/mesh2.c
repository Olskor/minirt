/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olskor <olskor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 13:44:08 by olskor            #+#    #+#             */
/*   Updated: 2024/01/12 12:40:02 by olskor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_Tri		create_triangle(t_Vec3 pos1, t_Vec3 pos2, t_Vec3 pos3);
t_box_tri	calculate_box(t_mesh mesh);
float		ft_atof(char *str);
void		free_split(char **split);
t_Vec3		*ft_append_pos(t_Vec3 *pos, t_Vec3 newpos, int i);

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

void	ft_split_tri(char *line, t_mesh *mesh, t_Vec3 *pos, int *j)
{
	char	**split;

	split = ft_split(line, ' ');
	if (split[1] && split[2] && split[3])
	{
		mesh->tri = ft_append_tri(mesh->tri,
				create_triangle(pos[ft_atoi(split[1]) - 1],
					pos[ft_atoi(split[2]) - 1],
					pos[ft_atoi(split[3]) - 1]), *j);
		*j = *j + 1;
	}
	free_split(split);
}

void	ft_split_pos(char *line, t_Vec3 **pos, int *i)
{
	char	**split;

	split = ft_split(line, ' ');
	if (split[1] && split[2] && split[3])
	{
		*pos = ft_append_pos(*pos, vec3(ft_atof(split[1]),
					ft_atof(split[2]), ft_atof(split[3])), *i);
		*i = *i + 1;
	}
	free_split(split);
}

t_mesh	read_obj(char *obj, t_data *d)
{
	t_mesh	mesh;
	t_Vec3	*pos;
	int		fd;
	char	*line;
	t_Int2	ij;

	ij = int2(0, 0);
	fd = open(obj, O_RDONLY);
	if (fd == -1)
		error_parse("Le fichier mesh est introuvable.", d);
	line = get_next_line(fd);
	while (line)
	{
		if (line[0] == 'v' && line[1] == ' ')
			ft_split_pos(line, &pos, &ij.x);
		if (line[0] == 'f' && line[1] == ' ')
			ft_split_tri(line, &mesh, pos, &ij.y);
		free(line);
		line = get_next_line(fd);
	}
	mesh.trinbr = ij.y;
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
