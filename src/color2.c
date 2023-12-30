/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olskor <olskor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 17:00:50 by olskor            #+#    #+#             */
/*   Updated: 2023/12/29 17:23:37 by olskor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_Col	saturatecol(t_Col col);

t_Col	mulcol(t_Col col1, t_Col col2)
{
	col1.t *= col2.t;
	col1.r *= col2.r;
	col1.g *= col2.g;
	col1.b *= col2.b;
	return (saturatecol(col1));
}

t_Col	scalecol(t_Col col1, double sampleperpixel)
{
	col1.t = col1.t * sampleperpixel;
	col1.r = col1.r * sampleperpixel;
	col1.g = col1.g * sampleperpixel;
	col1.b = col1.b * sampleperpixel;
	return (col1);
}

t_Col	lerpcol(t_Col col1, t_Col col2, float t)
{
	t_Col	ret;

	ret.t = lerp(col1.t, col2.t, t);
	ret.r = lerp(col1.r, col2.r, t);
	ret.g = lerp(col1.g, col2.g, t);
	ret.b = lerp(col1.b, col2.b, t);
	return (ret);
}
