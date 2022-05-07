/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   custom_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wroyal <wroyal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 17:40:22 by wroyal            #+#    #+#             */
/*   Updated: 2022/01/04 17:40:25 by wroyal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	update_output(char ***matrix, int fd)
{
	char	**buf;
	char	*temp;
	char	*line;

	buf = NULL;
	line = NULL;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		temp = ft_strtrim(line, "\n");
		free(line);
		buf = ft_extend_matrix(buf, temp);
		free(temp);
	}
	ft_free_matrix(matrix);
	*matrix = buf;
}

void	exec_cust(char ***out, char *full, char *args, char **envp)
{
	pid_t	pid;
	int		fd[2];
	char	**mass;

	pipe(fd);
	pid = fork();
	if (!pid)
	{
		close(fd[READ_END]);
		mass = ft_split(args, ' ');
		dup2(fd[WRITE_END], STDOUT_FILENO);
		close(fd[WRITE_END]);
		if (!access(full, F_OK))
			execve(full, mass, envp);
		exit (1);
	}
	close(fd[WRITE_END]);
	waitpid(pid, NULL, 0);
	update_output(out, fd[READ_END]);
	close(fd[READ_END]);
}
