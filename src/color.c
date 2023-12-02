/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olskor <olskor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 16:17:41 by jauffret          #+#    #+#             */
/*   Updated: 2023/11/02 23:44:17 by olskor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_Col saturatecol(t_Col col)
{
	if (col.t > 255)
		col.t = 255;
	if (col.r > 255)
		col.r = 255;
	if (col.g > 255)
		col.g = 255;
	if (col.b > 255)
		col.b = 255;
	return (col);
}

float	aces(float x)
{
	float	a;
	float	b;
	float	c;
	float	d;
	float	e;

	a = 2.51f;
	b = 0.03f;
	c = 2.43f;
	d = 0.59f;
	e = 0.14f;
	return (saturate((x * (a * x + b)) / (x * (c * x + d) + e)));
}

int	create_trgb(t_Col col)
{
	int	t;
	int	r;
	int	g;
	int	b;

	col.t = aces(col.t) * 255;
	col.r = aces(col.r) * 255;
	col.g = aces(col.g) * 255;
	col.b = aces(col.b) * 255;
	col = saturatecol(col);
	t = (int) col.t;
	r = (int) col.r;
	g = (int) col.g;
	b = (int) col.b;
	return (t << 24 | r << 16 | g << 8 | b);
}

t_Col col4(double t, double r, double g, double b)
{
	t_Col	ret;

	ret.t = t;
	ret.r = r;
	ret.g = g;
	ret.b = b;
	return (ret);
}

t_Col addcol(t_Col col1, t_Col col2)
{
	col1.t += col2.t;
	col1.r += col2.r;
	col1.g += col2.g;
	col1.b += col2.b;
	return (col1);
}

t_Col mulcol(t_Col col1, t_Col col2)
{
	col1.t *= col2.t;
	col1.r *= col2.r;
	col1.g *= col2.g;
	col1.b *= col2.b;
	return (saturatecol(col1));
}

t_Col scalecol(t_Col col1, double sampleperpixel)
{
	col1.t = col1.t * sampleperpixel;
	col1.r = col1.r * sampleperpixel;
	col1.g = col1.g * sampleperpixel;
	col1.b = col1.b * sampleperpixel;
	return (col1);
}
