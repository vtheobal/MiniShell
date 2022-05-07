/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wroyal <wroyal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 18:21:43 by wroyal            #+#    #+#             */
/*   Updated: 2022/01/04 16:41:58 by wroyal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*str;

	str = malloc(count * size);
	if (str == NULL)
		return (NULL);
	ft_bzero(str, size * count);
	return (str);
}
