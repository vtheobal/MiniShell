/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wroyal <wroyal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 13:14:07 by wroyal            #+#    #+#             */
/*   Updated: 2022/01/04 16:16:23 by wroyal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	l;
	char	*s3;

	i = 0;
	l = 0;
	if (s1 == 0 || s2 == 0)
		return (NULL);
	s3 = (char *)malloc(sizeof(char) * ((ft_strlen(s1) + ft_strlen(s2)) + 1));
	if (s3 == 0)
		return (NULL);
	while (s1[i] != '\0')
	{
		s3[i] = s1[i];
		i++;
	}
	while (s2[l] != '\0')
	{
		s3[i] = s2[l];
		i++;
		l++;
	}
	s3[i] = '\0';
	return (s3);
}
