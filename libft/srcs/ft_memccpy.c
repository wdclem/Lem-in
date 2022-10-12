/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccariou <ccariou@hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 18:41:30 by ccariou           #+#    #+#             */
/*   Updated: 2022/09/09 11:52:00 by ccariou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"
/* Function copies bytes from memory area source into destination
 * stopping after the first occurence of c has been copied
 * or after n bytes have been copied, whichever comes first.
*/

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t			index;
	unsigned char	*dest;
	unsigned char	*s;

	dest = (unsigned char *) dst;
	s = (unsigned char *) src;
	index = 0;
	while (index < n)
	{
		dest[index] = s[index];
		if (s[index] == (unsigned char) c)
			return ((void *)(dest + index + 1));
		index ++;
	}
	return (NULL);
}
