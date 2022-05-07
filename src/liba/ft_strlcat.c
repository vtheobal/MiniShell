/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wroyal <wroyal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 11:44:29 by wroyal            #+#    #+#             */
/*   Updated: 2022/01/04 16:16:25 by wroyal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	dst_len;
	size_t	src_len;

	i = 0;
	src_len = ft_strlen(src);
	while (*dst != '\0' && dstsize > 0)
	{
		dst++;
		i++;
		dstsize--;
	}
	dst_len = i;
	while (*src != '\0' && dstsize > 1)
	{
		*dst = *src;
		dst++;
		src++;
		dstsize--;
	}
	if (dstsize > 0 || *src == 0)
		*dst = '\0';
	return (dst_len + src_len);
}
