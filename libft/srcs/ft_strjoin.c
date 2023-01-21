/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccariou <ccariou@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 13:38:21 by ccariou           #+#    #+#             */
/*   Updated: 2022/09/09 11:52:11 by ccariou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"
/* Allocates and return a fresh string ending with '\0'
 * result of the concatenation of s1 and s2.
 */

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	len;
	size_t	i;

	if (s1 == NULL && s2 == NULL)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2);
	i = 0;
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (str == NULL)
		return (NULL);
	while (s1 && *s1)
	{
		str[i] = *s1;
		i ++;
		s1 ++;
	}
	while (s2 && *s2)
	{
		str[i] = *s2;
		i ++;
		s2 ++;
	}
	str[i] = '\0';
	return (str);
}
