/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccariou <ccariou@hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 11:02:16 by ccariou           #+#    #+#             */
/*   Updated: 2022/09/09 11:52:11 by ccariou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"
/* Function put the pointer to string source after dest up to n char long.
 */

char	*ft_strncat(char *s1, const char *s2, size_t n)
{
	size_t	i;
	size_t	len;
	char	*tmp;

	tmp = s1;
	i = 0;
	len = ft_strlen(s1);
	while (i < n && s2[i] != '\0')
	{
		s1[i + len] = s2[i];
		i ++;
	}
	s1[i + len] = '\0';
	return (tmp);
}
