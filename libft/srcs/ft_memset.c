/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccariou <ccariou@hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 20:54:35 by ccariou           #+#    #+#             */
/*   Updated: 2022/09/09 11:52:02 by ccariou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

/*
 * So the logic here is:
 * We want to fill the given amount of memory with the same char, right?
 * Char is one byte but we could also copy memory one long at a time -
 * 8 bytes at a time sounds a bit more faster than 1 byte.
 *
 * Char value can be turned into repeating long by multiplying it with
 * a very specific hexadecimal value - I originally found it by pure
 * brute force, but googling it will give interesting results too.
 *
 * Otherwise similar to "fast" memcpy - we copy long by long until len
 * is too short for long, then switch to int if possible and finally
 * copy last bytes one at a time. With longer len's we save considerable
 * amount of time, haven't really benchmarked with len < 8 so it might
 * be better it to have a check if it's even worth it to do the whole
 * long conversion thing.
 */

void	*ft_memset(void *b, int c, size_t len)
{
	long	blong;
	void	*ptr;

	blong = (long) c * 0x101010101010101;
	ptr = b;
	while (len >= sizeof(long))
	{
		*(long *) ptr = blong;
		ptr += sizeof(long);
		len -= sizeof(long);
	}
	if (len >= sizeof(int))
	{
		*(int *) ptr = (int) blong;
		ptr += sizeof(int);
		len -= sizeof(int);
	}
	while (len-- > 0)
		*(unsigned char *) ptr++ = (unsigned char) c;
	return (b);
}
