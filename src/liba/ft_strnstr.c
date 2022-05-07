/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wroyal <wroyal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 13:18:39 by wroyal            #+#    #+#             */
/*   Updated: 2022/01/04 16:16:34 by wroyal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	l;

	i = 0;
	l = 0;
	if (ft_strlen(needle) == 0)
		return ((char *)haystack);
	while (haystack[i] != '\0' && i < len)
	{
		l = 0;
		while (haystack[l + i] == needle[l] && (i + l) < len)
		{
			l++;
			if (needle[l] == '\0')
				return ((char *)&haystack[i]);
		}
		i++;
	}
	return (0);
}
