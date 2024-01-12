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

double	_valide_positif_non_nul(double d, char *msg, t_data *data)
{
	char	*err;

	if (d <= 0)
	{
		err = ft_strjoin(msg, " doit être positif et non nul");
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
	b_fail = b_fail || (v.x == 0 && v.y == 0 && v.z == 0);
	if (b_fail)
		error_parse("Vecteur Normal invalide (valeur non comprise entre -1 et 1, et ne peut être (0; 0; 0)).", d);
	return (v);
}

int	_valide_data(t_data *d)
{
	int b_fail;

	b_fail = (!d->cam) || (!d->light) || (!d->ambient) || (!d->wi);
	if (b_fail)
		error_parse("Il manque un Ambiant, une Camera, une Résolution ou une Light.\nCeci peut être dû à un fichier invalide.", d);
	return ( ! b_fail);
}
