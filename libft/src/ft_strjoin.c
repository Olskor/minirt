/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jauffret <jauffret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 14:07:47 by jauffret          #+#    #+#             */
/*   Updated: 2023/02/06 14:50:38 by jauffret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		len;
	int		i;
	char	*rst;

	if (!s1 || !s2)
		return (0);
	len = ft_strlen(s1) + ft_strlen(s2);
	rst = (char *)malloc(len + 1);
	i = 0;
	if (!rst)
		return (NULL);
	while (s1[i])
	{
		rst[i] = s1[i];
		i++;
	}
	len = 0;
	while (s2[len])
	{
		rst[i + len] = s2[len];
		len++;
	}
	rst[i + len] = 0;
	return (rst);
}
