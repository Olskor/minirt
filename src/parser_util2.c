/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_util2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbourgue <fbourgue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 11:22:13 by fbourgue          #+#    #+#             */
/*   Updated: 2024/01/10 11:22:28 by fbourgue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	error_parse(char *msg, t_data	*data);

double	_valide_positif(double d, char *msg, t_data *data)
{
	char	*err;

	if (d < 0)
	{
		err = ft_strjoin(msg, " doit être positif");
		error_parse(err, data);
		free (err);
	}
	return (d);
}
