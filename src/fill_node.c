/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_node.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wroyal <wroyal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 17:41:05 by wroyal            #+#    #+#             */
/*   Updated: 2022/01/04 17:41:06 by wroyal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static t_full	*mini_init(void)
{
	t_full	*mini;

	mini = malloc(sizeof(t_full));
	if (!mini)
		return (NULL);
	mini->full_cmd = NULL;
	mini->full_path = NULL;
	mini->in_file = STDIN_FILENO;
	mini->out_file = STDOUT_FILENO;
	return (mini);
}

static t_full	*get_params(t_data *p, t_full *node, char **t[2], int *i)
{
	if (t[0][*i])
	{
		if (t[0][*i][0] == '>' && t[0][*i + 1] && t[0][*i + 1][0] == '>')
			node = get_outfile2(p, node, t[1], i);
		else if (t[0][*i][0] == '>')
			node = get_outfile1(p, node, t[1], i);
		else if (t[0][*i][0] == '<' && t[0][*i + 1] && \
			t[0][*i + 1][0] == '<')
			node = get_infile2(p, node, t[1], i);
		else if (t[0][*i][0] == '<')
			node = get_infile1(p, node, t[1], i);
		else if (t[0][*i][0] != '|')
			node->full_cmd = ft_extend_matrix(node->full_cmd, t[1][*i]);
		else
		{
			shell_perror(p, PIPENDERR, NULL);
			*i = -2;
		}
		return (node);
	}
	shell_perror(p, PIPENDERR, NULL);
	*i = -2;
	return (node);
}

static char	**get_trimmed(char **args)
{
	char	**temp;
	char	*buff;
	int		j;

	j = -1;
	temp = ft_dup_matrix(args);
	while (temp && temp[++j])
	{
		buff = ft_strtrim_all(temp[j], 0, 0);
		free(temp[j]);
		temp[j] = buff;
	}
	return (temp);
}

static t_list	*stop_fill(t_list *cmds, char **args, char **temp)
{
	ft_lstclear(&cmds, free_content);
	ft_free_matrix(&temp);
	ft_free_matrix(&args);
	return (NULL);
}

t_list	*fill_nodes(t_data *prompt, char **args, int i)
{
	t_list	*cmds[2];
	char	**temp[2];

	cmds[0] = NULL;
	temp[1] = get_trimmed(args);
	while (args[++i])
	{
		cmds[1] = ft_lstlast(cmds[0]);
		if (i == 0 || (args[i][0] == '|' && args[i + 1] && args[i + 1][0]))
		{
			i += args[i][0] == '|';
			ft_lstadd_back(&cmds[0], ft_lstnew(mini_init()));
			cmds[1] = ft_lstlast(cmds[0]);
		}
		temp[0] = args;
		cmds[1]->content = get_params(prompt, cmds[1]->content, temp, &i);
		if (i < 0)
			return (stop_fill(cmds[0], args, temp[1]));
		if (!args[i])
			break ;
	}
	ft_free_matrix(&temp[1]);
	ft_free_matrix(&args);
	return (cmds[0]);
}
