/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wroyal <wroyal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 15:59:28 by wroyal            #+#    #+#             */
/*   Updated: 2022/01/04 16:16:41 by wroyal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*mas;
	size_t	len_s;
	size_t	i;

	i = 0;
	if (s == 0)
		return (0);
	len_s = ft_strlen(s);
	if (len > len_s)
		len = len_s;
	if (start >= len_s)
	{
		mas = malloc(1 * sizeof(char));
		mas[i] = '\0';
		return (mas);
	}
	mas = (char *)malloc(sizeof(char) * len + 1);
	if (mas == 0)
		return (0);
	while (i < len && start < len_s)
		mas[i++] = s[start++];
	mas[i] = '\0';
	return (mas);
}
