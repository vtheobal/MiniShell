/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wroyal <wroyal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 17:40:58 by wroyal            #+#    #+#             */
/*   Updated: 2022/01/04 17:40:59 by wroyal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*expand_path(char *str, int t, int quotes[2], char *var)
{
	char	*path;
	char	*aux;

	quotes[0] = 0;
	quotes[1] = 0;
	while (str && str[++t])
	{
		quotes[0] = (quotes[0] + (!quotes[1] && str[t] == '\'')) % 2;
		quotes[1] = (quotes[1] + (!quotes[0] && str[t] == '\"')) % 2;
		if (!quotes[0] && !quotes[1] && str[t] == '~' && (t == 0 || \
			str[t - 1] != '$'))
		{
			aux = ft_substr(str, 0, t);
			path = ft_strjoin(aux, var);
			free(aux);
			aux = ft_substr(str, t + 1, ft_strlen(str));
			free(str);
			str = ft_strjoin(path, aux);
			free(aux);
			free(path);
			return (expand_path(str, t + ft_strlen(var) - 1, quotes, var));
		}
	}
	free(var);
	return (str);
}

static char	*get_substr_var(char *str, int i, t_data *prompt)
{
	char	*aux;
	int		pos;
	char	*path;
	char	*var;

	pos = ft_strchars_i(&str[i], "|\"\'$?>< ") + (ft_strchr("$?", str[i]) != 0);
	if (pos == -1)
		pos = ft_strlen(str) - 1;
	aux = ft_substr(str, 0, i - 1);
	var = mini_getenv(&str[i], prompt->env_p, \
		ft_strchars_i(&str[i], "\"\'$|>< "));
	if (!var && str[i] == '$')
		var = ft_itoa(getpid());
	else if (!var && str[i] == '?')
		var = ft_itoa(prompt->env_status);
	path = ft_strjoin(aux, var);
	free(aux);
	aux = ft_strjoin(path, &str[i + pos]);
	free(var);
	free(path);
	free(str);
	return (aux);
}

char	*expand_vars(char *str, int t, int quotes[2], t_data *prompt)
{
	quotes[0] = 0;
	quotes[1] = 0;
	while (str && str[++t])
	{
		quotes[0] = (quotes[0] + (!quotes[1] && str[t] == '\'')) % 2;
		quotes[1] = (quotes[1] + (!quotes[0] && str[t] == '\"')) % 2;
		if (!quotes[0] && str[t] == '$' && str[t + 1] && \
			((ft_strchars_i(&str[t + 1], "/~%^{}:; ") && !quotes[1]) || \
			(ft_strchars_i(&str[t + 1], "/~%^{}:;\"") && quotes[1])))
			return (expand_vars(get_substr_var(str, ++t, prompt), -1, \
				quotes, prompt));
	}
	return (str);
}
