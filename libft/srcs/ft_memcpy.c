/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccariou <ccariou@hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 17:51:28 by ccariou           #+#    #+#             */
/*   Updated: 2022/09/09 11:52:01 by ccariou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"
/* Fucntion copies n char form memory area source to memory area dest
*/

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	void	*d1;

	d1 = dst;
	if (dst == src || n == 0)
		return (d1);
	while (n >= sizeof(long))
	{
		*(long *) d1 = *(const long *) src;
		d1 += sizeof(long);
		src += sizeof(long);
		n -= sizeof(long);
	}
	if (n >= sizeof(int))
	{
		*(int *) d1 = *(const int *) src;
		d1 += sizeof(int);
		src += sizeof(int);
		n -= sizeof(int);
	}
	while (n-- > 0)
		*(char *) d1++ = *(const char *) src++;
	return (dst);
}
