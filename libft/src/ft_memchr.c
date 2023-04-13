/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jauffret <jauffret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 11:29:16 by jauffret          #+#    #+#             */
/*   Updated: 2023/02/06 13:11:57 by jauffret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	*ft_memchr(const void *s, int c, int n)
{
	unsigned char	*str;

	if (!n)
		return (0);
	str = (unsigned char *)s;
	while (n > 1 && *str != (unsigned char)c)
	{
		n--;
		str++;
	}
	if (*str == (unsigned char)c)
		return ((void *)str);
	return (0);
}
