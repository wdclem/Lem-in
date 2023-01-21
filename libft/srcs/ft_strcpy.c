/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccariou <ccariou@hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 21:00:00 by ccariou           #+#    #+#             */
/*   Updated: 2022/09/09 11:52:10 by ccariou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"
/* Function copies the string pointed from source to destination.
*/

char	*ft_strcpy(char *dst, const char *src)
{
	int	index;

	index = 0;
	while (src[index] != '\0')
	{
		dst[index] = src[index];
		index ++;
	}
	dst[index] = '\0';
	return (dst);
}
