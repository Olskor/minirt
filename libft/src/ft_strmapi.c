/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jauffret <jauffret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 16:36:26 by jauffret          #+#    #+#             */
/*   Updated: 2023/02/06 15:00:15 by jauffret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*rst;
	int		i;

	if (!s || !f)
		return (0);
	rst = ft_strdup(s);
	if (!rst)
		return (NULL);
	i = 0;
	while (s[i])
	{
		rst[i] = f(i, s[i]);
		i++;
	}
	return (rst);
}
