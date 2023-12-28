/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   box.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olskor <olskor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 16:09:21 by olskor            #+#    #+#             */
/*   Updated: 2023/12/28 16:46:03 by olskor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_hit	hit_box1(t_box box, t_Ray ray, float t_min, float t_max)
{
	t_hit	hit;

	hit.hit = 0;
	return (hit);
}

t_hit	hit_box(t_data *data, t_Ray ray, t_hit hit)
{
	int		i;
	t_hit	hit_temp;

	i = 0;
	while (i < data->boxnbr)
	{
		hit_temp = hit_box1(data->box[i], ray, 0.001, hit.t_max);
		if (hit_temp.hit)
		{
			hit = hit_temp;
			hit.t_max = hit_temp.t;
		}
		i++;
	}
	return (hit);
}
