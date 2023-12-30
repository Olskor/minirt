//#include "minirt.h"
/*#include "../includes/fred.h"

t_Col	cr_col(t_Vec3 v)
{
	t_Col c;

	c.r = v.x / 255;
	c.g = v.y / 255;
	c.b = v.z / 255;
	c.t = 0;
	return (c);
}

char	*next(char **line)
{
	char	*ret;
	char	*next_coma;
	char	*next_space;

	next_coma = ft_strchr(*line, ',');
	next_space = ft_strchr(*line, ' ');
	if (next_space == 0  || (next_coma && (next_coma < next_space)))
		ret = ft_substr(*line, 0,next_coma - *line);
	else
		ret = ft_substr(*line, 0,next_space - *line);
	*line += ft_strlen(ret) + 1;
	return (ret);
}

void	_grab_col(t_Col *ret, char **line)
{
	int t_int[3];

	t_int[0] = 0;
	t_int[1] = 0;
	t_int[2] = 0;
	t_int[0] = ft_atoi(next(line));
	t_int[1] = ft_atoi(next(line));
	t_int[2] = ft_atoi(next(line));
	*ret = (cr_col(vec3(t_int[0], t_int[1], t_int[2])));
}

double	_double(char *params)
{
	double	r;
	double	deci;
	char			*dot;
	int	div;
	int	i;

	div = 1;
	r = ft_atoi(params);
	dot = ft_strchr(params, '.');
	if (! dot)
		return (r);
	i = ft_strlen(dot);
	while (--i > 0)
		div *= 10;
	deci = ft_atoi(++dot);
	if (r >= 0)
		r += (deci / div);
	else
		r -= (deci / div);
	return (r);
}

void	on_spaces(char **s_init)
{
	char	*c;
	char	**s = s_init;

	while (s && *s && (
			**s == ' ' || **s == '\t' || **s == '\n'
		)
	)
	{
		(*s)++;
	}
}

void	_grab_3_doubles(t_Vec3 *ret, char **line)
{
	double t_double[3];

	t_double[0] = 0;
	t_double[1] = 0;
	t_double[2] = 0;
	t_double[0] = _double(next(line));
	t_double[1] = _double(next(line));
	t_double[2] = _double(next(line));
	*ret = (vec3(t_double[0], t_double[1], t_double[2]));
}

t_sphere	*cr_sphere(char	**line)
{
	t_sphere*ret;

	(*line) += 2;
	on_spaces(line);
	ret = malloc(sizeof(t_sphere));
	 _grab_3_doubles(&ret->pos,line);
	on_spaces(line);
	ret->rad = ( _double(next(line)));
	on_spaces(line);
	_grab_col(&ret->mat.col, line);
	return (ret);
}

t_cam	*cr_camera(char	**line)
{
	t_cam*ret;

	(*line) += 1;
	on_spaces(line);
	ret = malloc(sizeof(t_cam));
	 _grab_3_doubles(&ret->pos,line);
	on_spaces(line);
	_grab_3_doubles(&ret->rot, line);
	on_spaces(line);
	ret->fov = (ft_atoi(next(line)));
	return (ret);
}

t_plane	*cr_plane(char	**line)
{
	t_plane	*ret;

	(*line) += 2;
	on_spaces(line);
	ret = malloc(sizeof(t_plane));
	 _grab_3_doubles(&ret->pos,line);
	on_spaces(line);
	_grab_3_doubles(&ret->norm, line);
	on_spaces(line);
	_grab_col(&ret->mat.col, line);
	return (ret);
}

t_cylinder	*cr_cylinder(char	**line)
{
	t_cylinder*ret;

	(*line) += 2;
	on_spaces(line);
	ret = malloc(sizeof(t_cylinder));
	 _grab_3_doubles(&ret->pos,line);
	on_spaces(line);
	_grab_3_doubles(&ret->rot, line);
	on_spaces(line);
	ret->rad = ( _double(next(line)));
	on_spaces(line);
	ret->h = ( _double(next(line)));
	on_spaces(line);
	_grab_col(&ret->mat.col, line);
	return (ret);
}*/

