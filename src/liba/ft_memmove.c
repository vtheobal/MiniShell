/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wroyal <wroyal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 11:15:54 by wroyal            #+#    #+#             */
/*   Updated: 2022/01/04 16:16:09 by wroyal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*ptr;
	unsigned char	*crt;

	ptr = (unsigned char *) dst;
	crt = (unsigned char *) src;
	i = 0;
	if (ptr + n < crt || crt >= ptr)
		return (ft_memcpy(dst, src, n));
	while (n > 0)
	{
		if (dst == NULL && src == NULL)
			return (0);
		ptr[n - 1] = crt[n - 1];
		n--;
	}
	return (dst);
}
