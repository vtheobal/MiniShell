/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr_i.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wroyal <wroyal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 17:45:24 by wroyal            #+#    #+#             */
/*   Updated: 2022/01/04 17:45:25 by wroyal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_strchr_i(const char *s, int c)
{
	unsigned char	c_unsigned;
	int				i;

	i = 0;
	if (!s)
		return (-1);
	c_unsigned = (unsigned char)c;
	while (s[i] != '\0')
	{
		if (s[i] == c_unsigned)
			return (i);
		i++;
	}
	if (c_unsigned == '\0')
		return (i);
	return (-1);
}
