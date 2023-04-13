/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olskor <olskor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 12:36:42 by jauffret          #+#    #+#             */
/*   Updated: 2023/04/14 00:09:35 by olskor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "mlx.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <X11/keysym.h>
# include <math.h>

# ifndef HEIGHT
#  define HEIGHT 1080
# endif
# ifndef WIDTH
#  define WIDTH 1920
# endif

typedef struct s_Vec3
{
	double	x;
	double	y;
	double	z;
}		t_Vec3;

typedef struct s_Vec4
{
	double	x;
	double	y;
	double	z;
	double	w;
}		t_Vec4;

typedef struct s_Int2
{
	int	x;
	int	y;
}		t_Int2;

typedef struct s_Ray
{
	t_Vec3	orig;
	t_Vec3	dir;
}		t_Ray;

typedef struct s_Col
{
	int	r;
	int	g;
	int	b;
	int	t;
}		t_Col;

typedef struct s_Mat
{
	t_Col	col;
	float	rough;
	float	metal;
	float	refr;
}		t_Mat;

typedef struct s_Tri
{
	t_Vec3	pos1;
	t_Vec3	pos2;
	t_Vec3	pos3;
}		t_Tri;

typedef struct s_mesh
{
	t_Tri	*tri;
	t_Mat	mat;
	t_Vec3	pos;
	t_Vec4	rot;
}		t_mesh;

typedef struct s_sphere
{
	float	rad;
	t_Mat	mat;
	t_Vec3	pos;
	t_Vec4	rot;
}		t_sphere;

typedef struct s_plane
{
	t_Vec3	pos;
	t_Vec3	norm;
	t_Mat	mat;
}	t_plane;

typedef	struct s_cam
{
	float	aspect;
	float	vwi;
	float	vhe;
	float	focal;
	t_Vec3	pos;
	t_Vec4	rot;
}	t_cam;

typedef struct s_img
{
	void	*mlx_img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_img;

typedef struct s_data	t_data;
struct s_data
{
	void		*mlx;
	void		*win;
	int			wi;
	int			he;
	int			frame;
	t_img		img;
	t_sphere	*sphere;
	t_plane		*plane;
	t_cam		cam;
};

t_Vec3		vec3(double x, double y, double z);
t_Vec3		vecat(t_Ray ray, double t);
t_Vec3		addvec3(t_Vec3 u, t_Vec3 v);
t_Vec3		subvec3(t_Vec3 u, t_Vec3 v);
t_Vec3		mulvec3(t_Vec3 u, t_Vec3 v);
t_Vec3		scalevec3(t_Vec3 u, double v);
double		dot(t_Vec3 u, t_Vec3 v);
t_Vec3		cross(t_Vec3 u, t_Vec3 v);
double		vec3length2(t_Vec3 u);
double		vec3length(t_Vec3 u);
t_Vec3		unit_vec3(t_Vec3 u);
int			get_sign(int i);
t_Int2		int2(float x, float y);
void		img_pix_put(t_img *img, int x, int y, int color);
int			render(t_data *data);
int			loop(t_data *data);
int			mouse_handle(int button, int x, int y, t_data *data);
int			input_next(int keysym, t_data *data);
int			handle_input(int keysym, t_data *data);
int			close_window(t_data *data);
float		max(float x, float y);
float		min(float x, float y);
float		saturate(float x);
int			create_trgb(int t, int r, int g, int b);
int			get_t(int trgb);
int			get_r(int trgb);
int			get_g(int trgb);
int			get_b(int trgb);
void		hook_setup(t_data *data);

#endif