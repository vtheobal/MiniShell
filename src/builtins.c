/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wroyal <wroyal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 17:40:14 by wroyal            #+#    #+#             */
/*   Updated: 2022/01/04 18:09:42 by wroyal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	shell_builtin(t_data *prompt, t_list *cmd, int *is_exit, int n)
{
	char	**ij;

	while (cmd)
	{
		ij = ((t_full *)cmd->content)->full_cmd;
		n = 0;
		if (ij)
			n = ft_strlen(*ij);
		if (ij && !ft_strncmp(*ij, "exit", n) && n == 4)
			prompt->env_status = shell_exit(cmd, is_exit);
		else if (!cmd->next && ij && !ft_strncmp(*ij, "cd", n) && n == 2)
			prompt->env_status = shell_cd(prompt);
		else if (!cmd->next && ij && !ft_strncmp(*ij, "export", n) && n == 6)
			prompt->env_status = shell_export(prompt);
		else if (!cmd->next && ij && !ft_strncmp(*ij, "unset", n) && n == 5)
			prompt->env_status = shell_unset(prompt);
		else
		{
			signal(SIGINT, handle_sigint_child);
			signal(SIGQUIT, handle_sigquit);
			exec_cmd(prompt, cmd);
		}
		cmd = cmd->next;
	}
	return (prompt->env_status);
}

int	is_builtin(t_full *n)
{
	int		g;

	if (!n->full_cmd)
		return (0);
	if ((n->full_cmd && ft_strchr(*n->full_cmd, '/')) || (n->full_path && \
		ft_strchr(n->full_path, '/')))
		return (0);
	g = ft_strlen(*n->full_cmd);
	if (!ft_strncmp(*n->full_cmd, "pwd", g) && g == 3)
		return (1);
	if (!ft_strncmp(*n->full_cmd, "env", g) && g == 3)
		return (1);
	if (!ft_strncmp(*n->full_cmd, "cd", g) && g == 2)
		return (1);
	if (!ft_strncmp(*n->full_cmd, "export", g) && g == 6)
		return (1);
	if (!ft_strncmp(*n->full_cmd, "unset", g) && g == 5)
		return (1);
	if (!ft_strncmp(*n->full_cmd, "echo", g) && g == 4)
		return (1);
	if (!ft_strncmp(*n->full_cmd, "exit", g) && g == 4)
		return (1);
	return (0);
}

int	shell_cd(t_data *prompt)
{
	char	*home_dir;
	char	**argv;
	char	*pwd;

	argv = ((t_full *)prompt->list_cmd->content)->full_cmd;
	pwd = getcwd(NULL, 0);
	home_dir = mini_getenv("HOME", prompt->env_p, 4);
	if (!argv[1])
		chdir(home_dir);
	free(home_dir);
	if (argv[1] && access(argv[1], F_OK) != -1)
		chdir(argv[1]);
	else if (argv[1])
	{
		shell_perror(prompt, NDIR, argv[1]);
		free(pwd);
		return (1);
	}
	prompt->env_p = mini_setenv("OLDPWD", pwd, prompt->env_p, 6);
	free(pwd);
	pwd = getcwd(NULL, 0);
	prompt->env_p = mini_setenv("PWD", pwd, prompt->env_p, 3);
	free(pwd);
	return (0);
}

int	shell_pwd(void)
{
	char	*buf;

	buf = getcwd(NULL, 0);
	ft_putendl_fd(buf, 1);
	free(buf);
	return (0);
}

int	shell_echo(t_list *cmd)
{
	int		new_line;
	int		i[2];
	char	**argv;
	t_full	*node;

	i[0] = 0;
	i[1] = 0;
	new_line = 1;
	node = cmd->content;
	argv = node->full_cmd;
	while (argv && argv[++i[0]])
	{
		if (!i[1] && !ft_strncmp(argv[i[0]], "-n", 3))
			new_line = 0;
		else
		{
			i[1] = 1;
			ft_putstr_fd(argv[i[0]], 1);
			if (argv[i[0] + 1])
				ft_putchar_fd(' ', 1);
		}
	}
	if (new_line)
		ft_putchar_fd('\n', 1);
	return (0);
}
