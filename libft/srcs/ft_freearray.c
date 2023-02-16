/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_freearray.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccariou <ccariou@hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 09:38:19 by ccariou           #+#    #+#             */
/*   Updated: 2022/10/03 11:26:41 by ccariou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"
/* Function to free array/2d array
 */

void	ft_freearray(void ***array, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		free((*array)[i]);
		i++;
	}
	free(*array);
	*array = NULL;
}
