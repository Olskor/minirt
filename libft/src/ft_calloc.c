/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jauffret <jauffret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 13:25:06 by jauffret          #+#    #+#             */
/*   Updated: 2023/02/06 13:03:14 by jauffret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*tab;
	size_t	len;

	len = (size_t)(size * nmemb);
	if (size == 0 || nmemb == 0)
		return (malloc(0));
	if (len / size != nmemb || len / nmemb != size)
		return (NULL);
	tab = malloc(len);
	if (tab)
		ft_bzero(tab, len);
	return (tab);
}
