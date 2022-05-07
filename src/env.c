/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wroyal <wroyal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 17:40:35 by wroyal            #+#    #+#             */
/*   Updated: 2022/01/04 17:40:38 by wroyal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*mini_getenv(char *var, char **envp, int t)
{
	int	i;
	int	t2;

	i = 0;
	if (t < 0)
		t = ft_strlen(var);
	while (!ft_strchr(var, '=') && envp && envp[i])
	{
		t2 = t;
		if (t2 < ft_strchr_i(envp[i], '='))
			t2 = ft_strchr_i(envp[i], '=');
		if (!ft_strncmp(envp[i], var, t2))
			return (ft_substr(envp[i], t2 + 1, ft_strlen(envp[i])));
		i++;
	}
	return (NULL);
}

char	**mini_setenv(char *var, char *value, char **envp, int t)
{
	int		i[2];
	char	*aux[2];

	if (t < 0)
		t = ft_strlen(var);
	i[0] = -1;
	aux[0] = ft_strjoin(var, "=");
	aux[1] = ft_strjoin(aux[0], value);
	free(aux[0]);
	while (!ft_strchr(var, '=') && envp && envp[++i[0]])
	{
		i[1] = t;
		if (i[1] < ft_strchr_i(envp[i[0]], '='))
			i[1] = ft_strchr_i(envp[i[0]], '=');
		if (!ft_strncmp(envp[i[0]], var, i[1]))
		{
			aux[0] = envp[i[0]];
			envp[i[0]] = aux[1];
			free(aux[0]);
			return (envp);
		}
	}
	envp = ft_extend_matrix(envp, aux[1]);
	free(aux[1]);
	return (envp);
}

static int	var_in_envp(char *argv, char **envp, int ij[2])
{
	int	pos;

	ij[1] = 0;
	pos = ft_strchr_i(argv, '=');
	if (pos == -1)
		return (-1);
	while (envp[ij[1]])
	{
		if (!ft_strncmp(envp[ij[1]], argv, pos + 1))
			return (1);
		ij[1]++;
	}
	return (0);
}

int	shell_export(t_data *prompt)
{
	int		ij[2];
	int		pos;
	char	**argv;

	argv = ((t_full *)prompt->list_cmd->content)->full_cmd;
	if (ft_matrixlen(argv) >= 2)
	{
		ij[0] = 1;
		while (argv[ij[0]])
		{
			pos = var_in_envp(argv[ij[0]], prompt->env_p, ij);
			if (pos == 1)
			{
				free(prompt->env_p[ij[1]]);
				prompt->env_p[ij[1]] = ft_strdup(argv[ij[0]]);
			}
			else if (!pos)
				prompt->env_p = ft_extend_matrix(prompt->env_p, argv[ij[0]]);
			ij[0]++;
		}
	}
	return (0);
}

int	shell_unset(t_data *prompt)
{
	char	**argv;
	char	*aux;
	int		ij[2];

	ij[0] = 0;
	argv = ((t_full *)prompt->list_cmd->content)->full_cmd;
	if (ft_matrixlen(argv) >= 2)
	{
		while (argv[++ij[0]])
		{
			if (argv[ij[0]][ft_strlen(argv[ij[0]]) - 1] != '=')
			{
				aux = ft_strjoin(argv[ij[0]], "=");
				free(argv[ij[0]]);
				argv[ij[0]] = aux;
			}
			if (var_in_envp(argv[ij[0]], prompt->env_p, ij))
				ft_matrix_replace_in(&prompt->env_p, NULL, ij[1]);
		}
	}
	return (0);
}
