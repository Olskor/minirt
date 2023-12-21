/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olskor <olskor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 14:58:44 by olskor            #+#    #+#             */
/*   Updated: 2023/12/21 15:06:43 by olskor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

float	pseudorand(t_data *data)
{
	unsigned int	ret;
	unsigned int	result;

	ret = data->rand;
	ret = ret * 747796405 + 2891336453;
	result = ((ret >> ((ret >> 28) + 4)) ^ ret) * 277803737;
	result = (result >> 22) ^ result;
	if (data->rand == 4294967295)
		data->rand = 0;
	data->rand++;
	return (((float) result / 4294967295));
}

t_Vec3	vec3rand(double min, double max, t_data *data)
{
	t_Vec3	ret;
	double	amp;

	amp = max - min;
	ret.x = pseudorand(data) * amp + min;
	ret.y = pseudorand(data) * amp + min;
	ret.z = pseudorand(data) * amp + min;
	return (ret);
}

t_Vec3	random_in_unit_sphere(t_data *data)
{
	t_Vec3	p;

	while (1)
	{
		p = vec3rand(-1, 1, data);
		if (vec3length2(p) >= 1)
			continue ;
		return (p);
	}
}

t_Vec3	lambertian_random_ray(t_Vec3 normal, t_data *data)
{
	t_Vec3	random;
	t_Vec3	target;

	random = random_in_unit_sphere(data);
	target = addvec3(normal, random);
	target = unit_vec3(target);
	return (target);
}
