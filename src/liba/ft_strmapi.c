/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wroyal <wroyal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 15:24:46 by wroyal            #+#    #+#             */
/*   Updated: 2022/01/04 16:16:31 by wroyal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*ss;

	if (s == 0 || f == 0)
		return (0);
	ss = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (ss == 0)
		return (0);
	i = 0;
	while (s[i] != '\0')
	{
		ss[i] = (*f)(i, s[i]);
		i++;
	}
	ss[i] = '\0';
	return (ss);
}
