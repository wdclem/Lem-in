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
/* Function copies unsigned char c to the first n char of the string
 * pointd to by argument str.
*/

void	*ft_memset(void *b, int c, size_t n)
{
	unsigned char	*s;

	s = (unsigned char *)b;
	while (n--)
		*s++ = c;
	return (b);
}
