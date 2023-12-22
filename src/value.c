/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   value.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olskor <olskor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 15:23:38 by jauffret          #+#    #+#             */
/*   Updated: 2023/12/22 18:20:14 by olskor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

float	max(float x, float y)
{
	if (x >= y)
		return (x);
	return (y);
}

float	min(float x, float y)
{
	if (x <= y)
		return (x);
	return (y);
}

float	saturate(float x)
{
	if (x > 1.0)
		return (1.0);
	if (x < 0.0)
		return (0.0);
	return (x);
}

float	lerp(float a, float b, float t)
{
	return (a + t * (b - a));
}
