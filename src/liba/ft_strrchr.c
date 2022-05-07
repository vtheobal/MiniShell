/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wroyal <wroyal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 20:11:55 by wroyal            #+#    #+#             */
/*   Updated: 2022/01/04 16:16:36 by wroyal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;

	i = 0;
	while (*s != '\0')
	{
		s++;
		i++;
	}
	if (c == '\0' && *s == '\0')
		return ((char *) s);
	s--;
	while (i != 0)
	{
		if (*s == (unsigned char) c)
			return ((char *) s);
		s--;
		i--;
	}
	return (NULL);
}
