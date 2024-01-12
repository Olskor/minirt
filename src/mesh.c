/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olskor <olskor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 19:02:20 by olskor            #+#    #+#             */
/*   Updated: 2024/01/12 14:57:46 by olskor           ###   ########.fr       */
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
	box.min = vec3(0, 0, 0);
	box.max = vec3(0, 0, 0);
	if (mesh.trinbr == 0)
		return (box);
	box.min = mesh.tri[0].pos1;
	box.max = mesh.tri[0].pos1;
	while (i < mesh.trinbr)
	{
		box.min = minvec3(box.min, mesh.tri[i].pos1);
		box.max = maxvec3(box.max, mesh.tri[i].pos1);
		box.min = minvec3(box.min, mesh.tri[i].pos2);
		box.max = maxvec3(box.max, mesh.tri[i].pos2);
		box.min = minvec3(box.min, mesh.tri[i].pos3);
		box.max = maxvec3(box.max, mesh.tri[i].pos3);
		i++;
	}
	return (box);
}

float	ft_atof(char *str)
{
	float	result;
	float	sign;
	float	factor;
	int		i;

	result = 0;
	i = 0;
	sign = 1.0;
	if (str[i] == '-')
		sign = -1.0 + 0 * i++;
	while (str[i] >= '0' && str[i] <= '9')
		result = result * 10.0 + (str[i++] - '0');
	if (str[i] == '.')
	{
		factor = 0.1;
		i++;
		while (str[i] >= '0' && str[i] <= '9')
		{
			result += (str[i] - '0') * factor;
			factor *= 0.1;
			i++;
		}
	}
	return (result * sign);
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
