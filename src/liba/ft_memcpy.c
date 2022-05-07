/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wroyal <wroyal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 15:41:26 by wroyal            #+#    #+#             */
/*   Updated: 2022/01/04 16:14:45 by wroyal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	int		i;
	char	*ptr;
	char	*crt;

	ptr = (char *) dst;
	crt = (char *) src;
	i = 0;
	if (dst == 0 && src == 0)
		return (NULL);
	while (n > 0)
	{
		ptr[i] = crt[i];
		i++;
		n--;
	}
	return (dst);
}
