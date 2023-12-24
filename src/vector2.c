/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olskor <olskor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 04:26:22 by olskor            #+#    #+#             */
/*   Updated: 2023/12/24 04:40:13 by olskor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_Vec4	vec4(double x, double y, double z, double w)
{
	t_Vec4	ret;

	ret.x = x;
	ret.y = y;
	ret.z = z;
	ret.w = w;
	return (ret);
}

t_Vec3	rotatevec3(t_Vec3 vector, t_Vec3 dir, t_Vec3 up)
{
	t_Vec3	ret;

	ret.x = vector.x * dir.x + vector.y * dir.y + vector.z * dir.z;
	ret.y = vector.x * up.x + vector.y * up.y + vector.z * up.z;
	ret.z = vector.x * cross(dir, up).x + vector.y * cross(dir, up).y
		+ vector.z * cross(dir, up).z;
	return (ret);
}