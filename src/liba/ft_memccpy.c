/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wroyal <wroyal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 15:16:07 by wroyal            #+#    #+#             */
/*   Updated: 2022/01/04 16:14:35 by wroyal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char	*ptr;
	unsigned char	*crt;
	size_t			i;

	ptr = (unsigned char *)dst;
	crt = (unsigned char *)src;
	i = 0;
	while (i < n)
	{
		ptr[i] = crt[i];
		if (ptr[i] == (unsigned char) c)
			return ((dst + i + 1));
		i++;
	}
	return (0);
}
