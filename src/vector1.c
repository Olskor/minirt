/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jauffret <jauffret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 16:13:45 by jauffret          #+#    #+#             */
/*   Updated: 2023/04/13 18:52:36 by jauffret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	dot(t_Vec3 u, t_Vec3 v)
{
	double	a;

	a = u.x * v.x;
	a += u.y * v.y;
	a += u.z * v.z;
	return (a);
}

t_Vec3	cross(t_Vec3 u, t_Vec3 v)
{
	return (vec3(u.y * v.z - u.z * v.y,
			u.z * v.x - u.x * v.z,
			u.x * v.y - u.y * v.x));
}

double	vec3length2(t_Vec3 u)
{
	return (u.x * u.x + u.y * u.y + u.z * u.z);
}

double	vec3length(t_Vec3 u)
{
	return (sqrt(vec3length2(u)));
}

t_Vec3	unit_vec3(t_Vec3 u)
{
	return (scalevec3(u, 1 / vec3length(u)));
}
