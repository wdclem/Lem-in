/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccariou <ccariou@hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 21:14:11 by ccariou           #+#    #+#             */
/*   Updated: 2022/09/09 11:52:12 by ccariou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"
/* Function copies source to destination up to n char.
*/

char	*ft_strncpy(char *dst, const char *src, size_t len)
{
	size_t	index;

	index = 0;
	while (src[index] != '\0' && index < len)
	{
		dst[index] = src[index];
		index ++;
	}
	while (index < len)
	{
		dst[index] = '\0';
		index ++;
	}
	return (dst);
}
