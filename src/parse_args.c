/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wroyal <wroyal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 17:42:03 by wroyal            #+#    #+#             */
/*   Updated: 2022/01/04 17:42:04 by wroyal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static char	**split_all(char **args, t_data *prompt)
{
	char	**subsplit;
	int		i;
	int		quotes[2];

	i = -1;
	while (args && args[++i])
	{
		args[i] = expand_vars(args[i], -1, quotes, prompt);
		args[i] = expand_path(args[i], -1, quotes, \
			mini_getenv("HOME", prompt->env_p, 4));
		subsplit = ft_cmd_subsplit(args[i], "<|>");
		ft_matrix_replace_in(&args, subsplit, i);
		i += ft_matrixlen(subsplit) - 1;
		ft_free_matrix(&subsplit);
	}
	return (args);
}

static void	*parse_args(char **args, t_data *p)
{
	int	is_exit;

	is_exit = 0;
	p->list_cmd = fill_nodes(p, split_all(args, p), -1);
	if (!p->list_cmd)
		return (p);
	p->env_status = shell_builtin(p, p->list_cmd, &is_exit, 0);
	if (p->env_status > 255)
		p->env_status = p->env_status / 255;
	if (args && is_exit)
	{
		ft_lstclear(&p->list_cmd, free_content);
		return (NULL);
	}
	return (p);
}

void	*check_args(char *out, t_data *p)
{
	char	**a;
	t_full	*n;

	if (!out)
	{
		printf("exit\n");
		return (NULL);
	}
	if (out[0] != '\0')
		add_history(out);
	a = ft_cmd_trim(out, " ");
	free(out);
	if (!a)
		shell_perror(p, QUOTE, NULL);
	if (!a)
		return ("");
	p = parse_args(a, p);
	if (p && p->list_cmd)
		n = p->list_cmd->content;
	if (p && p->list_cmd && n && n->full_cmd && ft_lstsize(p->list_cmd) == 1)
		p->env_p = mini_setenv("_", n->full_cmd[ft_matrixlen(n->full_cmd) - 1], \
			p->env_p, 1);
	if (p && p->list_cmd)
		ft_lstclear(&p->list_cmd, free_content);
	return (p);
}
