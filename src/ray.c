/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olskor <olskor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 18:14:25 by olskor            #+#    #+#             */
/*   Updated: 2023/12/22 18:16:06 by olskor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_Vec3	reflect(t_Vec3 v, t_Vec3 n)
{
	double	val;
	t_Vec3	ret;

	val = dot(n, v) * 2;
	ret = subvec3(v, scalevec3(n, val));
	ret = scalevec3(ret, 1);
	return (ret);
}

float	fresnel(t_hit hit, t_Ray ray)
{
	return (saturate((hit.mat.smooth * (1
					- saturate(1 * -dot(hit.norm, ray.dir))))));
}

t_Vec3	lerpvec3(t_Vec3 u, t_Vec3 v, float val)
{
	t_Vec3	ret;

	ret.x = v.x * val + u.x * (1 - val);
	ret.y = v.y * val + u.y * (1 - val);
	ret.z = v.z * val + u.z * (1 - val);
	return (ret);
}

t_Ray	newray(t_Vec3 orig, t_Vec3 dir)
{
	t_Ray	ray;

	ray.orig = orig;
	ray.dir = dir;
	return (ray);
}
