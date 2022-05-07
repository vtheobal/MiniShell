/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wroyal <wroyal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 17:11:52 by wroyal            #+#    #+#             */
/*   Updated: 2022/01/04 16:14:32 by wroyal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_nbrlen(long n)
{
	int		lenn;

	lenn = 0;
	if (n == 0)
	{
		lenn++;
		return (lenn);
	}
	if (n < 0)
	{
		n = n * -1;
		lenn++;
	}
	while (n > 0)
	{
		n = n / 10;
		lenn++;
	}
	return (lenn);
}

char	ft_guard(char *str, long i)
{
	if (i == 0)
	{
		str[0] = 48;
		return (*str);
	}
	return (str[0]);
}

char	*ft_itoa(int n)
{
	char	*str;
	long	i;
	int		lenn;

	i = n;
	lenn = ft_nbrlen(i);
	str = (char *)malloc(sizeof(char) * lenn + 1);
	if (str == 0)
		return (0);
	str[lenn--] = '\0';
	ft_guard(str, i);
	if (i < 0)
	{
		str[0] = '-';
		i = i * -1;
	}
	while (i > 0)
	{
		str[lenn] = 48 + (i % 10);
		i = i / 10;
		lenn--;
	}
	return (str);
}
