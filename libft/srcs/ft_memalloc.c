/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccariou <ccariou@hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 18:30:48 by ccariou           #+#    #+#             */
/*   Updated: 2022/09/09 11:52:00 by ccariou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	*ft_memalloc(size_t size)
{
	char	*memory;

	memory = malloc(size);
	if (memory == NULL || size == 0)
		return (NULL);
	while (size)
	{
		size --;
		memory[size] = '\0';
	}
	return (memory);
}
