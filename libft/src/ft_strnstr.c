/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jauffret <jauffret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 15:06:38 by jauffret          #+#    #+#             */
/*   Updated: 2023/02/06 18:18:23 by jauffret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (!big && len == 0)
		return (NULL);
	if (!little[0])
		return ((char *)big);
	if (ft_strlen(big) < ft_strlen(little) || ft_strlen(little) > len)
		return (0);
	while (big[i])
	{
		j = 0;
		while (big[i + j] == little[j] && i + j < len
			&& big[i + j] && little[j])
		{
			j++;
			if (!little[j] || j == len)
				return ((char *) big + i);
		}
		i++;
	}
	return (0);
}
