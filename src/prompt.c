/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wroyal <wroyal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 17:42:09 by wroyal            #+#    #+#             */
/*   Updated: 2022/01/04 18:08:47 by wroyal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	g_fds[2][2];

void	readline_child(t_data *prompt, char *str, char *out, int is_null)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
	close(g_fds[0][READ_END]);
	close(g_fds[1][READ_END]);
	out = readline(str);
	write(g_fds[0][WRITE_END], out, ft_strlen(out));
	is_null = !out;
	write(g_fds[1][WRITE_END], &prompt->env_status, sizeof(int));
	free(out);
	close(g_fds[0][WRITE_END]);
	close(g_fds[1][WRITE_END]);
	exit(is_null);
}

char	*shell_readline(t_data *prompt, char *str)
{
	pid_t	pid;
	int		is_null;
	char	*out;

	is_null = 0;
	out = NULL;
	if (!shell_here_fd(prompt, g_fds[0], g_fds[1]))
		return (NULL);
	pid = fork();
	if (pid == -1)
		shell_perror(prompt, FORKERR, NULL);
	if (!pid)
		readline_child(prompt, str, out, is_null);
	close(g_fds[0][WRITE_END]);
	close(g_fds[1][WRITE_END]);
	waitpid(pid, &is_null, 0);
	out = get_next_line(g_fds[0][READ_END]);
	if (!is_null && !out)
		out = ft_strdup("");
	read(g_fds[1][READ_END], &prompt->env_status, sizeof(int));
	close(g_fds[0][READ_END]);
	close(g_fds[1][READ_END]);
	return (out);
}
