/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmdsubsplit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wroyal <wroyal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 17:43:04 by wroyal            #+#    #+#             */
/*   Updated: 2022/01/04 17:43:14 by wroyal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	ft_count_words(char *s, char *set, int count)
{
	int		t[2];
	int		i;

	i = 0;
	t[0] = 0;
	t[1] = 0;
	while (s && s[i] != '\0')
	{
		count++;
		if (!ft_strchr(set, s[i]))
		{
			while ((!ft_strchr(set, s[i]) || t[0] || t[1]) && s[i] != '\0')
			{
				t[0] = (t[0] + (!t[1] && s[i] == '\'')) % 2;
				t[1] = (t[1] + (!t[0] && s[i] == '\"')) % 2;
				i++;
			}
			if (t[0] || t[1])
				return (-1);
		}
		else
			i++;
	}
	return (count);
}

static char	**ft_fill_array(char **buff, char *s, char *set, int i[3])
{
	int		q[2];

	q[0] = 0;
	q[1] = 0;
	while (s && s[i[0]] != '\0')
	{
		i[1] = i[0];
		if (!ft_strchr(set, s[i[0]]))
		{
			while ((!ft_strchr(set, s[i[0]]) || q[0] || q[1]) && s[i[0]])
			{
				q[0] = (q[0] + (!q[1] && s[i[0]] == '\'')) % 2;
				q[1] = (q[1] + (!q[0] && s[i[0]] == '\"')) % 2;
				i[0]++;
			}
		}
		else
			i[0]++;
		buff[i[2]++] = ft_substr(s, i[1], i[0] - i[1]);
	}
	return (buff);
}

char	**ft_cmd_subsplit(char const *s, char *set)
{
	char	**buff;
	int		nwords;
	int		i[3];

	i[0] = 0;
	i[1] = 0;
	i[2] = 0;
	if (!s)
		return (NULL);
	nwords = ft_count_words((char *)s, set, 0);
	if (nwords == -1)
		return (NULL);
	buff = malloc((nwords + 1) * sizeof(char *));
	if (buff == NULL)
		return (NULL);
	buff = ft_fill_array(buff, (char *)s, set, i);
	buff[nwords] = NULL;
	return (buff);
}
