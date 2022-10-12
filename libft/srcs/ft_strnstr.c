/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccariou <ccariou@hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 19:14:01 by ccariou           #+#    #+#             */
/*   Updated: 2022/09/09 11:52:12 by ccariou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;
	char	*src;
	char	*tofind;

	tofind = (char *) needle;
	src = (char *) haystack;
	i = 0;
	if (needle[0] == '\0')
		return (src);
	while (src[i] && i < len)
	{
		j = 0;
		while (i + j < len && src[i + j] == tofind[j])
		{
			if (!tofind[j + 1])
			{
				return (src + i);
			}
			j ++;
		}
		i ++;
	}
	return (NULL);
}
