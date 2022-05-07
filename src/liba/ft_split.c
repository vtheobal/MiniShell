/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wroyal <wroyal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 13:47:08 by wroyal            #+#    #+#             */
/*   Updated: 2022/01/04 16:16:19 by wroyal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_numword(char *str, char c)
{
	int	i;
	int	flag;
	int	l;

	flag = 1;
	l = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] != c && flag == 1)
		{
			flag = 0;
			l++;
		}
		while (str[i] == c && flag == 0)
			flag = 1;
		i++;
	}
	return (l);
}

char	**ft_free(char **news)
{
	int		i;

	i = 0;
	while (news[i] != 0)
	{
		free(news[i]);
		i++;
	}
	free(news);
	return (0);
}

char	*ft_word(char *str, char c)
{
	char	*news;
	int		k;

	k = 0;
	while (str[k] != '\0' && str[k] != c)
		k++;
	news = (char *)malloc(sizeof(char) * k + 1);
	if (news == 0)
		return (*ft_free(&news));
	k = 0;
	while (str[k] != '\0' && str[k] != c)
	{
		news[k] = str[k];
		k++;
	}
	news[k] = '\0';
	return (news);
}

char	**ft_split(char const *s, char c)
{
	char	**news;
	int		i;

	i = 0;
	if ((s == 0 && c == 0) || s == 0)
		return (0);
	news = (char **)malloc(sizeof(char *) * (ft_numword((char *)s, c) + 1));
	if (news == 0)
		return (0);
	while (*s != '\0')
	{
		while (*s != '\0' && *s == c)
			s++;
		if (*s != '\0')
		{
			news[i] = ft_word((char *)s, c);
			i++;
			while (*s != '\0' && *s != c)
				s++;
		}
	}
	news[i] = 0;
	return (news);
}
