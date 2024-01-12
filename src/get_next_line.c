/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olskor <olskor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 15:53:58 by jauffret          #+#    #+#             */
/*   Updated: 2024/01/12 11:55:11 by olskor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft.h"

char	*ft_free_buffer(char *ret, char *buffer)
{
	char	*temp;

	temp = ft_strjoin(ret, buffer);
	free(ret);
	return (temp);
}

char	*ft_get_line(char *buffer)
{
	char	*line;
	int		i;

	i = 0;
	if (!buffer)
		return (0);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] != '\n' && i == 0)
		return (0);
	line = ft_calloc(i + 2, 1);
	if (!line)
		return (0);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
	{
		line[i] = buffer[i];
		i++;
	}
	if (buffer[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

char	*ft_get_next(char *buffer)
{
	int		i;
	int		j;
	char	*line;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!buffer[i])
	{
		free(buffer);
		return (NULL);
	}
	line = ft_calloc((ft_strlen(buffer) - i + 1), sizeof(char));
	i++;
	j = 0;
	while (buffer[i])
		line[j++] = buffer[i++];
	free(buffer);
	return (line);
}

char	*read_file(int fd, char *ret)
{
	char	*buffer;
	int		i;

	i = 1;
	if (!ret)
		ret = ft_calloc(1, 1);
	buffer = ft_calloc(BUFFER_SIZE + 1, 1);
	while (i > 0)
	{
		i = read(fd, buffer, BUFFER_SIZE);
		if (i == -1)
		{
			free (buffer);
			free (ret);
			return (0);
		}
		buffer[i] = '\0';
		ret = ft_free_buffer(ret, buffer);
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	free(buffer);
	return (ret);
}

char	*get_next_line(int fd)
{
	static char	*buffer[4096];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer[fd] = read_file(fd, buffer[fd]);
	if (!buffer[fd])
		return (NULL);
	line = ft_get_line(buffer[fd]);
	buffer[fd] = ft_get_next(buffer[fd]);
	return (line);
}
