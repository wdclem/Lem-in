/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccariou <ccariou@hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 13:13:03 by ccariou           #+#    #+#             */
/*   Updated: 2022/09/09 11:52:10 by ccariou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"
/* Function search for the first occurence of the char c, in the string str.
 */

char	*ft_strchr(const char *s, int c)
{
	if (s)
	{
		while ((*s != '\0') && (*s != c))
			s ++;
		if (*s == c)
			return ((char *) s);
	}
	return (0);
}
