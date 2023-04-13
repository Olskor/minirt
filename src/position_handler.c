/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   position_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jauffret <jauffret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 16:36:45 by jauffret          #+#    #+#             */
/*   Updated: 2023/04/13 19:42:52 by jauffret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	get_sign(int i)
{
	if (i >= 0)
		return (1);
	return (-1);
}

t_Vec3	vecat(t_Ray ray, double t)
{
	return (addvec3(ray.orig, scalevec3(ray.dir, t)));
}

t_Int2	int2(float x, float y)
{
	t_Int2	pos;

	pos.x = x;
	pos.y = y;
	return (pos);
}
