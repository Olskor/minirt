/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olskor <olskor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 12:36:42 by jauffret          #+#    #+#             */
/*   Updated: 2023/12/28 16:41:53 by olskor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "mlx.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <X11/keysym.h>
# include <fcntl.h>
# include <math.h>

# include "../includes/libft.h"
# include "../includes/get_next_line.h"

# ifndef HEIGHT
#  define HEIGHT 1080
# endif
# ifndef WIDTH
#  define WIDTH 1920
# endif
# ifndef MAX_SAMPLES
#  define MAX_SAMPLES 100
# endif
# ifndef MAX_FRAMES
#  define MAX_FRAMES 1
# endif
# ifndef MAX_BOUNCES
#  define MAX_BOUNCES 3
# endif
# define M_PI 3.14159265358979323846

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
	double	r;
	double	g;
	double	b;
	double	t;
}		t_Col;

typedef struct s_Tex
{
	int		res;
	t_Col	**img;
}		t_Tex;

typedef struct s_Mat
{
	t_Col	col;
	float	smooth;
	float	metal;
	t_Tex	*tex;
	t_Tex	*bump;
	t_Tex	*pbr;
}		t_Mat;

typedef struct s_mesh	t_mesh;

typedef struct s_Tri
{
	t_Vec3	pos1;
	t_Vec3	pos2;
	t_Vec3	pos3;
	t_mesh	*mesh;
}		t_Tri;

typedef struct s_box_tri
{
	t_Vec3	min;
	t_Vec3	max;
}		t_box_tri;

struct s_mesh
{
	t_Tri	*tri;
	int		trinbr;
	t_Mat	mat;
	t_Vec3	pos;
	t_Vec3	dir;
	t_Vec3	up;
	t_Vec3	scale;
	t_box_tri	box;
};

typedef struct s_light
{
	t_Vec3	pos;
	t_Col	col;
	float	intensity;
}		t_light;

typedef struct s_sky
{
	t_Vec3	sun;
	float	intensity;
	int		active;
}		t_sky;

typedef struct s_sphere
{
	float	rad;
	t_Mat	mat;
	t_Vec3	pos;
}		t_sphere;

typedef struct s_plane
{
	t_Vec3	pos;
	t_Vec3	norm;
	t_Mat	mat;
}	t_plane;

typedef struct s_box
{
	t_Vec3	max;
	t_Vec3	min;
	t_Vec3	dir;
	t_Vec3	up;
	t_Mat	mat;
}	t_box;

typedef struct s_cylinder
{
	float	rad;
	float	h;
	t_Mat	mat;
	t_Vec3	pos;
	t_Vec3	dir;
}	t_cylinder;


typedef struct s_hit
{
	float	t;
	float	t_max;
	int		hit;
	int		frontface;
	t_Vec3	p;
	t_Vec3	norm;
	t_Mat	mat;
	t_Vec3	uv;
}	t_hit;

typedef struct s_cam
{
	float	aspect;
	float	focal;
	float	fov;
	t_Vec3	pos;
	t_Vec3	rot;
	float	vwi;
	float	vhe;
	t_Vec3	vup;
	t_Vec3	u;
	t_Vec3	v;
	t_Vec3	w;
	t_Vec3	v_u;
	t_Vec3	v_v;
	t_Vec3	v_ul;
	t_Vec3	pixdu;
	t_Vec3	pixdv;
	t_Vec3	pix00;
}	t_cam;

typedef struct s_img
{
	void	*mlx_img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
	int		wi;
	int		he;
}	t_img;

typedef struct s_data	t_data;
struct s_data
{
	void			*mlx;
	void			*win;
	int				wi;
	int				he;
	int				sample;
	t_img			img;
	t_Col			**cimg;
	t_light			*light;
	int				lightnbr;
	t_sky			sky;
	t_sphere		*sphere;
	int				spherenbr;
	t_plane			*plane;
	int				planenbr;
	t_cylinder		*cylinder;
	int				cylindernbr;
	t_box			*box;
	int				boxnbr;
	t_mesh			*mesh;
	int				meshnbr;
	unsigned int	rand;
	int				bounces;
	t_cam			cam;
	t_Col			ambient;
	int				frame;
};

t_Vec3		vec3(double x, double y, double z);
t_Vec3		vecat(t_Ray ray, double t);
t_Vec3		addvec3(t_Vec3 u, t_Vec3 v);
t_Vec3		subvec3(t_Vec3 u, t_Vec3 v);
t_Vec3		mulvec3(t_Vec3 u, t_Vec3 v);
t_Vec3		scalevec3(t_Vec3 u, double v);
t_Vec3		rotatevec3(t_Vec3 vector, t_Vec3 dir, t_Vec3 up);
t_Vec4		vec4(double x, double y, double z, double w);
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
int			create_trgb(t_Col col);
t_Col		mulcol(t_Col col1, t_Col col2);
t_Col		col4(double t, double r, double g, double b);
t_Col		addcol(t_Col col1, t_Col col2);
t_Col		scalecol(t_Col col1, double sampleperpixel);
void		hook_setup(t_data *data);
float		lerp(float a, float b, float t);
float		aces(float x);
float		pseudorand(t_data *data);
t_Vec3		vec3rand(double min, double max, t_data *data);
t_Vec3		random_in_unit_sphere(t_data *data);
t_Vec3		lambertian_random_ray(t_Vec3 normal, t_data *data);
t_hit		hit_sphere(t_data *data, t_Ray ray, t_hit hit);
t_hit		hit_plane(t_data *data, t_Ray ray, t_hit hit);
t_hit		hit_cylinder(t_data *data, t_Ray ray, t_hit hit);
t_hit		hit_light(t_data *data, t_Ray ray, t_hit hit);
t_hit		hit_cone(t_data *data, t_Ray ray, t_hit hit);
void		img_pix_put(t_img *img, int x, int y, int color);
int			render_background(t_img *img, int color);
void		load(char	*path, t_data *data);
t_Vec3		reflect(t_Vec3 v, t_Vec3 n);
float		fresnel(t_hit hit, t_Ray ray);
t_Vec3		lerpvec3(t_Vec3 u, t_Vec3 v, float val);
t_Ray		newray(t_Vec3 orig, t_Vec3 dir);
t_Col		raycol(t_Ray ray, t_data *data, int depth);
void		save_img(t_data *data);
t_mesh		read_obj(char *obj);
t_hit		hit_mesh(t_data *data, t_Ray ray, t_hit hit);
t_mesh		translate_mesh(t_mesh mesh);
t_mesh		rotate_mesh(t_mesh mesh);
t_mesh		scale_mesh(t_mesh mesh);
t_box		calculate_box(t_mesh mesh);
t_Tex		*checker_tex(void);
t_Tex		*rainbowtex(void);
t_Col		get_texcol(t_Tex *tex, t_Vec3 uv);
t_Col		raycol(t_Ray ray, t_data *data, int depth);
t_Col		lerpcol(t_Col col1, t_Col col2, float t);
t_Tex		*load_img(char *path, t_data *data);


#endif
