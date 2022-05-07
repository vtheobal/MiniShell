/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wroyal <wroyal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 17:41:56 by wroyal            #+#    #+#             */
/*   Updated: 2022/01/04 18:09:00 by wroyal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static t_data	init_vars(t_data prompt, char *str, char **argv, char **env_p)
{
	char	*num;

	str = getcwd(NULL, 0);
	prompt.env_p = mini_setenv("PWD", str, prompt.env_p, 3);
	free(str);
	str = mini_getenv("SHLVL", env_p, 5);
	if (!str || ft_atoi(str) <= 0)
		num = ft_strdup("1");
	else
		num = ft_itoa(ft_atoi(str) + 1);
	free(str);
	prompt.env_p = mini_setenv("SHLVL", num, prompt.env_p, 5);
	free(num);
	str = mini_getenv("PATH", prompt.env_p, 4);
	if (!str)
		prompt.env_p = mini_setenv("PATH", \
		"/usr/local/sbin:/usr/local/bin:/usr/bin:/bin", prompt.env_p, 4);
	free(str);
	str = mini_getenv("_", prompt.env_p, 1);
	if (!str)
		prompt.env_p = mini_setenv("_", argv[0], prompt.env_p, 1);
	free(str);
	return (prompt);
}

static t_data	init_prompt(char **argv, char **env_p)
{
	t_data		prompt;
	char		*str;

	str = NULL;
	prompt.list_cmd = NULL;
	prompt.env_p = ft_dup_matrix(env_p);
	prompt.env_status = 0;
	prompt = init_vars(prompt, str, argv, env_p);
	return (prompt);
}

int	main(int argc, char **argv, char **env_p)
{
	char				*out;
	t_data				prompt;

	prompt = init_prompt(argv, env_p);
	while (argv && argc)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, SIG_IGN);
		out = shell_readline(&prompt, "\033[34;1mminishell \033[32;1m$> \033[0m");
		if (!check_args(out, &prompt))
			break ;
	}
	ft_free_matrix(&prompt.env_p);
	exit(prompt.env_status);
}
