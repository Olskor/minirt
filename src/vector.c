/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jauffret <jauffret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 16:13:45 by jauffret          #+#    #+#             */
/*   Updated: 2023/04/13 18:23:17 by jauffret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_Vec3	vec3(double x, double y, double z)
{
	t_Vec3	ret;

	ret.x = x;
	ret.y = y;
	ret.z = z;
	return (ret);
}

t_Vec3	addvec3(t_Vec3 u, t_Vec3 v)
{
	t_Vec3	ret;

	ret.x = u.x + v.x;
	ret.y = u.y + v.y;
	ret.z = u.z + v.z;
	return (ret);
}

t_Vec3	subvec3(t_Vec3 u, t_Vec3 v)
{
	t_Vec3	ret;

	ret.x = u.x - v.x;
	ret.y = u.y - v.y;
	ret.z = u.z - v.z;
	return (ret);
}

t_Vec3	mulvec3(t_Vec3 u, t_Vec3 v)
{
	t_Vec3	ret;

	ret.x = u.x * v.x;
	ret.y = u.y * v.y;
	ret.z = u.z * v.z;
	return (ret);
}

t_Vec3	scalevec3(t_Vec3 u, double v)
{
	t_Vec3	ret;

	ret.x = u.x * v;
	ret.y = u.y * v;
	ret.z = u.z * v;
	return (ret);
}
