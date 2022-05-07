/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wroyal <wroyal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 14:57:48 by wroyal            #+#    #+#             */
/*   Updated: 2022/01/04 16:16:39 by wroyal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	s;
	char	*ss1;

	if (!s1 || !set)
		return (NULL);
	while (*s1 && ft_strchr(set, *s1))
		s1++;
	s = ft_strlen(s1);
	while (s && ft_strchr(set, s1[s]))
		s--;
	ss1 = ft_substr((char *)s1, 0, s + 1);
	return (ss1);
}
