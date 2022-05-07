/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim_all.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wroyal <wroyal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 17:45:41 by wroyal            #+#    #+#             */
/*   Updated: 2022/01/04 17:45:43 by wroyal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	malloc_len(char const *s1)
{
	int	count;
	int	i;
	int	dquote;
	int	squote;

	i = 0;
	count = 0;
	dquote = 0;
	squote = 0;
	while (s1 && s1[i])
	{
		squote = (squote + (!dquote && s1[i] == '\'')) % 2;
		dquote = (dquote + (!squote && s1[i] == '\"')) % 2;
		if ((s1[i] == '\"' && !squote) || (s1[i] == '\'' && !dquote))
			count++;
		i++;
	}
	if (squote || dquote)
		return (-1);
	return (count);
}

char	*ft_strtrim_all(char const *str1, int squote, int dquote)
{
	int		count;
	int		i[2];
	char	*trim;

	i[1] = -1;
	i[0] = 0;
	count = malloc_len(str1);
	if (!str1 || count == -1)
		return (NULL);
	trim = malloc(sizeof(char) * (ft_strlen(str1) - count + 1));
	if (!trim)
		return (NULL);
	while (str1[i[0]])
	{
		squote = (squote + (!dquote && str1[i[0]] == '\'')) % 2;
		dquote = (dquote + (!squote && str1[i[0]] == '\"')) % 2;
		if ((str1[i[0]] != '\"' || squote) && (str1[i[0]] != '\'' || dquote) \
			&& ++i[1] >= 0)
			trim[i[1]] = str1[i[0]];
		i[0]++;
	}
	trim[++i[1]] = '\0';
	return (trim);
}
