/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putmatrix_fd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wroyal <wroyal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 17:45:11 by wroyal            #+#    #+#             */
/*   Updated: 2022/01/04 17:45:12 by wroyal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_putmatrix_fd(char **m, int fd)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (m && m[i])
	{
		count += ft_putendl_fd(m[i], fd);
		i++;
	}
	return (count);
}
