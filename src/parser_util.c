/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbourgue <fbourgue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 23:27:20 by fbourgue          #+#    #+#             */
/*   Updated: 2023/12/30 00:37:48 by fbourgue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_Col	scalecolParser(t_Col col1, double sampleperpixel)
{
	col1.t = col1.t * sampleperpixel;
	col1.r = col1.r * sampleperpixel;
	col1.g = col1.g * sampleperpixel;
	col1.b = col1.b * sampleperpixel;
	return (col1);
}

int	ft_atoi_free_param(char *str)
{
	int	ret;

	ret = ft_atoi(str);
	free(str);
	return (ret);
}
