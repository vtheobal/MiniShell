/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wroyal <wroyal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 19:00:29 by wroyal            #+#    #+#             */
/*   Updated: 2022/01/04 16:16:21 by wroyal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*ft_strdup(const char *s1)
{
	char	*mas;
	int		i;
	int		l;

	i = 0;
	l = 0;
	while (s1[l] != '\0')
		l++;
	mas = malloc(sizeof(char) * l + 1);
	if (mas == NULL)
		return (NULL);
	while (s1[i] != '\0')
	{
		mas[i] = s1[i];
		i++;
	}
	mas[i] = '\0';
	return (mas);
}
