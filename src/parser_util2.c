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

t_Vec3	_valide_vect_norm(t_Vec3 v, t_data *d)
{
	int	b_fail;

	b_fail = 0;
	b_fail = v.x > 1 || v.x < -1 || v.y > 1 || v.y < -1 || v.z > 1 || v.z < -1;
	if (b_fail)
		error_parse("Vecteur Normal invalide (valeur non comprise entre -1 et 1).", d);
	return (v);
}
