/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wroyal <wroyal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 17:40:45 by wroyal            #+#    #+#             */
/*   Updated: 2022/01/04 17:40:46 by wroyal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	*shell_perror(t_data *prompt, int err, char *param)
{
	prompt->env_status = 1;
	if (err == PIPENDERR)
		prompt->env_status = 2;
	if (err == QUOTE)
		ft_putstr_fd("minishell: error while looking for matching quote\n", 2);
	else if (err == NDIR)
		ft_putstr_fd("minishell: No such file or directory: ", 2);
	else if (err == NPERM)
		ft_putstr_fd("minishell: permission denied: ", 2);
	else if (err == NCMD)
		ft_putstr_fd("minishell: command not found: ", 2);
	else if (err == DUPERR)
		ft_putstr_fd("minishell: dup2 failed\n", 2);
	else if (err == FORKERR)
		ft_putstr_fd("minishell: fork failed\n", 2);
	else if (err == PIPERR)
		ft_putstr_fd("minishell: error creating pipe\n", 2);
	else if (err == PIPENDERR)
		ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
	else if (err == MEM)
		ft_putstr_fd("minishell: no memory left on device\n", 2);
	ft_putendl_fd(param, 2);
	return (NULL);
}

int	ft_atoi2(const char *nptr, long *nbm)
{
	int		sign;

	sign = 1;
	*nbm = 0;
	while (ft_isspace(*nptr))
		nptr++;
	if (*nptr == '-')
		sign = -sign;
	if (*nptr == '-' || *nptr == '+')
		nptr++;
	if (!ft_isdigit(*nptr))
		return (-1);
	while (ft_isdigit(*nptr))
	{
		*nbm = 10 * *nbm + (*nptr - '0');
		nptr++;
	}
	if (*nptr && !ft_isspace(*nptr))
		return (-1);
	*nbm *= sign;
	return (0);
}

int	shell_exit(t_list *cmd, int *is_exit)
{
	t_full	*node_js;
	long	status[2];

	node_js = cmd->content;
	*is_exit = !cmd->next;
	if (*is_exit)
		ft_putstr_fd("exit\n", 2);
	if (!node_js->full_cmd || !node_js->full_cmd[1])
		return (0);
	status[1] = ft_atoi2(node_js->full_cmd[1], &status[0]);
	if (status[1] == -1)
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(node_js->full_cmd[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		return (255);
	}
	else if (node_js->full_cmd[2])
	{
		*is_exit = 0;
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		return (1);
	}
	status[0] %= 256 + 256 * (status[0] < 0);
	return (status[0]);
}

void	free_content(void *temp)
{
	t_full	*node_js;

	node_js = temp;
	ft_free_matrix(&node_js->full_cmd);
	free(node_js->full_path);
	if (node_js->in_file != STDIN_FILENO)
		close(node_js->in_file);
	if (node_js->out_file != STDOUT_FILENO)
		close(node_js->out_file);
	free(node_js);
}
