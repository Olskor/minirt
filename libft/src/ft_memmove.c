/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jauffret <jauffret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 12:15:40 by jauffret          #+#    #+#             */
/*   Updated: 2023/02/05 14:06:38 by jauffret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	*ft_memmove(void *dest, const void *src, int n)
{
	char	*dst;
	char	*str;

	if (!dest && !src)
		return (0);
	str = (char *)src;
	dst = (char *)dest;
	if (src > dest)
	{
		while (n > 0)
		{
			*dst = *str;
			n--;
			dst++;
			str++;
		}
		return (dest);
	}
	while (n > 0)
	{
		n--;
		*(dst + n) = *(str + n);
	}
	return (dest);
}
