/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_low_level2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbourgue <fbourgue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 11:16:19 by fbourgue          #+#    #+#             */
/*   Updated: 2024/01/10 11:19:27 by fbourgue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	on_spaces(char **s_init)
{
	char	**s;

	s = s_init;
	while (s && *s && (
			**s == ' ' || **s == '\t' || **s == '\n'
		)
	)
	{
		(*s)++;
	}
}

char	*ft_spacechr(const char *s)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != ' ' && s[i] != '\t' && s[i] != '\n')
		i++;
	if (s[i] == ' ' || s[i] == '\t' || s[i] != '\n')
		return ((char *) s + i);
	return (0);
}
