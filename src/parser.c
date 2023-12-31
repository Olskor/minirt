/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olskor <olskor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 16:28:39 by fbourgue          #+#    #+#             */
/*   Updated: 2023/12/31 17:46:38 by olskor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	on_spaces(char **s_init);
char	*next(char **line);
double	_double(char *params);
void	_grab_3_doubles(t_Vec3 *ret, char **line);
int		ft_atoi_free_param(char *str);

t_Col	cr_col(t_Vec3 v)
{
	t_Col	c;

	c.r = v.x / 255;
	c.g = v.y / 255;
	c.b = v.z / 255;
	c.t = 0;
	return (c);
}

void	_grab_col(t_Col *ret, char **line)
{
	int	t_int[3];

	t_int[0] = 0;
	t_int[1] = 0;
	t_int[2] = 0;
	t_int[0] = ft_atoi_free_param(next(line));
	t_int[1] = ft_atoi_free_param(next(line));
	t_int[2] = ft_atoi_free_param(next(line));
	*ret = (cr_col(vec3(t_int[0], t_int[1], t_int[2])));
}

t_Col	*cr_ambient(char	**line)
{
	t_Col	*ret;
	double	intensity;

	(*line) += 1;
	on_spaces(line);
	intensity = _double(next(line));
	ret = malloc(sizeof(t_Col));
	_grab_col(ret, line);
	*ret = scalecolParser(*ret, intensity);
	return (ret);
}

t_light	*cr_light(char	**line)
{
	t_light	*ret;

	(*line) += 1;
	on_spaces(line);
	ret = malloc(sizeof(t_light));
	_grab_3_doubles(&ret->pos, line);
	on_spaces(line);
	ret->intensity = (_double(next(line)));
	on_spaces(line);
	_grab_col(&ret->col, line);
	return (ret);
}

t_cam	*cr_camera(char	**line)
{
	t_cam	*ret;

	(*line) += 1;
	on_spaces(line);
	ret = malloc(sizeof(t_cam));
	_grab_3_doubles(&ret->pos, line);
	on_spaces(line);
	_grab_3_doubles(&ret->rot, line);
	ret->rot = addvec3(ret->rot, ret->pos);
	on_spaces(line);
	ret->vup = vec3(0, 1, 0);
	ret->fov = ft_atoi_free_param(next(line));
	return (ret);
}
