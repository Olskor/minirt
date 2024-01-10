/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbourgue <fbourgue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 11:38:33 by fbourgue          #+#    #+#             */
/*   Updated: 2024/01/10 12:13:34 by fbourgue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

char	*_comment(int fd, char *sline, char **line)
{
	free (sline);
	*line = get_next_line (fd);
	sline = *line;
	return (sline);
}
