/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_params.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wroyal <wroyal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 18:14:30 by wroyal            #+#    #+#             */
/*   Updated: 2022/01/04 18:14:31 by wroyal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	get_fd(t_data *prompt, int oldfd, char *path, int flags[2])
{
	int	fd;

	if (oldfd > 2)
		close(oldfd);
	if (!path)
		return (-1);
	if (access(path, F_OK) == -1 && !flags[0])
		shell_perror(prompt, NDIR, path);
	else if (!flags[0] && access(path, R_OK) == -1)
		shell_perror(prompt, NPERM, path);
	else if (flags[0] && access(path, W_OK) == -1 && access(path, F_OK) == 0)
		shell_perror(prompt, NPERM, path);
	if (flags[0] && flags[1])
		fd = open(path, O_CREAT | O_WRONLY | O_APPEND, 0666);
	else if (flags[0] && !flags[1])
		fd = open(path, O_CREAT | O_WRONLY | O_TRUNC, 0666);
	else if (!flags[0] && oldfd != -1)
		fd = open(path, O_RDONLY);
	else
		fd = oldfd;
	return (fd);
}

t_full	*get_outfile1(t_data *prompt, t_full *node, char **args, int *t)
{
	char	*nl;
	int		flags[2];

	flags[0] = 1;
	flags[1] = 0;
	nl = "minishell: syntax error near unexpected token `newline'";
	(*t)++;
	if (args[*t])
		node->out_file = get_fd(prompt, node->out_file, args[*t], flags);
	if (!args[*t] || node->out_file == -1)
	{
		*t = -1;
		if (node->out_file != -1)
		{
			ft_putendl_fd(nl, 2);
			prompt->env_status = 2;
		}
		else
			prompt->env_status = 1;
	}
	return (node);
}

t_full	*get_outfile2(t_data *prompt, t_full *node, char **args, int *t)
{
	char	*nl;
	int		flags[2];

	flags[0] = 1;
	flags[1] = 1;
	nl = "minishell: syntax error near unexpected token `newline'";
	(*t)++;
	if (args[++(*t)])
		node->out_file = get_fd(prompt, node->out_file, args[*t], flags);
	if (!args[*t] || node->out_file == -1)
	{
		*t = -1;
		if (node->out_file != -1)
		{
			ft_putendl_fd(nl, 2);
			prompt->env_status = 2;
		}
		else
			prompt->env_status = 1;
	}
	return (node);
}

t_full	*get_infile1(t_data *prompt, t_full *node, char **args, int *t)
{
	char	*nl;
	int		flags[2];

	flags[0] = 0;
	flags[1] = 0;
	nl = "minishell: syntax error near unexpected token `newline'";
	(*t)++;
	if (args[*t])
		node->in_file = get_fd(prompt, node->in_file, args[*t], flags);
	if (!args[*t] || node->in_file == -1)
	{
		*t = -1;
		if (node->in_file != -1)
		{
			ft_putendl_fd(nl, 2);
			prompt->env_status = 2;
		}
		else
			prompt->env_status = 1;
	}
	return (node);
}

t_full	*get_infile2(t_data *prompt, t_full *node, char **args, int *t)
{
	char	*aux[2];
	char	*tmp;
	char	*str[2];

	str[0] = NULL;
	str[1] = NULL;
	aux[0] = NULL;
	aux[1] = "minishell: warning: here-document delimited by end-of-file";
	tmp = "minishell: syntax error near unexpected token `newline'";
	(*t)++;
	if (args[++(*t)])
	{
		aux[0] = args[*t];
		node->in_file = get_here_doc(prompt, str, 0, aux);
	}
	if (!args[*t] || node->in_file == -1)
	{
		*t = -1;
		if (node->in_file != -1)
		{
			ft_putendl_fd(tmp, 2);
			prompt->env_status = 2;
		}
	}
	return (node);
}
