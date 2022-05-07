/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wroyal <wroyal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 17:40:51 by wroyal            #+#    #+#             */
/*   Updated: 2022/01/04 17:40:52 by wroyal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	child_builtin(t_data *prompt, t_full *g, int r, t_list *cmd)
{
	if (!is_builtin(g) && g->full_cmd)
		execve(g->full_path, g->full_cmd, prompt->env_p);
	else if (g->full_cmd && !ft_strncmp(*g->full_cmd, "pwd", r) \
		&& r == 3)
		prompt->env_status = shell_pwd();
	else if (is_builtin(g) && g->full_cmd && \
		!ft_strncmp(*g->full_cmd, "echo", r) && r == 4)
		prompt->env_status = shell_echo(cmd);
	else if (is_builtin(g) && g->full_cmd && \
		!ft_strncmp(*g->full_cmd, "env", r) && r == 3)
	{
		ft_putmatrix_fd(prompt->env_p, 1);
		prompt->env_status = 0;
	}
}

static void	*child_redir(t_data *prompt, t_list *cmd, int fd[2])
{
	t_full	*node;

	node = cmd->content;
	if (node->in_file != STDIN_FILENO)
	{
		if (dup2(node->in_file, STDIN_FILENO) == -1)
			return (shell_perror(prompt, DUPERR, NULL));
		close(node->in_file);
	}
	if (node->out_file != STDOUT_FILENO)
	{
		if (dup2(node->out_file, STDOUT_FILENO) == -1)
			return (shell_perror(prompt, DUPERR, NULL));
		close(node->out_file);
	}
	else if (cmd->next && dup2(fd[WRITE_END], STDOUT_FILENO) == -1)
		return (shell_perror(prompt, DUPERR, NULL));
	close(fd[WRITE_END]);
	return ("");
}

void	*child_process(t_data *prompt, t_list *cmd, int fd[2])
{
	t_full	*n;
	int		l;

	n = cmd->content;
	l = 0;
	if (n->full_cmd)
		l = ft_strlen(*n->full_cmd);
	child_redir(prompt, cmd, fd);
	close(fd[READ_END]);
	child_builtin(prompt, n, l, cmd);
	ft_lstclear(&prompt->list_cmd, free_content);
	exit(prompt->env_status);
}

void	*check_to_fork(t_data *prompt, t_list *cmd, int fd[2])
{
	t_full	*n;
	pid_t	pid;

	n = cmd->content;
	if (n->in_file == -1 || n->out_file == -1)
		return (NULL);
	if ((n->full_path && access(n->full_path, X_OK) == 0) || is_builtin(n))
	{
		pid = fork();
		if (pid < 0)
		{
			close(fd[READ_END]);
			close(fd[WRITE_END]);
			return (shell_perror(prompt, FORKERR, NULL));
		}
		else if (!pid)
			child_process(prompt, cmd, fd);
		if (!cmd->next)
			waitpid(pid, &prompt->env_status, 0);
	}
	else if (!is_builtin(n) && n->full_path && access(n->full_path, F_OK) == 0)
		prompt->env_status = 126;
	else if (!is_builtin(n) && n->full_cmd)
		prompt->env_status = 127;
	return ("");
}

void	*exec_cmd(t_data *prompt, t_list *cmd)
{
	int		fd[2];

	get_cmd(prompt, cmd, NULL, NULL);
	if (pipe(fd) == -1)
		return (shell_perror(prompt, PIPERR, NULL));
	if (!check_to_fork(prompt, cmd, fd))
		return (NULL);
	close(fd[WRITE_END]);
	if (cmd->next && !((t_full *)cmd->next->content)->in_file)
		((t_full *)cmd->next->content)->in_file = fd[READ_END];
	else
		close(fd[READ_END]);
	return (NULL);
}
