/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbourgue <fbourgue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 11:38:33 by fbourgue          #+#    #+#             */
/*   Updated: 2024/01/12 16:41:54 by fbourgue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

char	*_text_fail_back(char **params)
{
	char	*ret;

	if (params && *params && **params && (ft_strlen(*params) > 0))
	{
		ret = next(params);
		return (ret);
	}
	else
		return (NULL);
}

char	*_comment(int fd, char *sline, char **line)
{
	free (sline);
	*line = get_next_line (fd);
	sline = *line;
	return (sline);
}

void	_config_error(char *line, t_data *d)
{
	char	*err;

	if (*line)
	{
		err = ft_strjoin ("Problème de configuration :\n", line);
		error_parse (err, d);
		free (err);
	}
}
