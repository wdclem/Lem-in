/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccariou <ccariou@hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 17:53:14 by ccariou           #+#    #+#             */
/*   Updated: 2022/09/09 11:52:12 by ccariou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"
/* Allocates and return a copy of a given str without whitespace
 */

char	*ft_strtrim(char const *s)
{
	char	*str;
	int		i;
	int		j;
	int		len;

	if (s == NULL)
		return (NULL);
	i = 0;
	j = ft_strlen(s);
	while (*s && (s[i] == ' ' || s[i] == '\t' || s[i] == '\n'))
		i ++;
	while (*s && (s[j - 1] == ' ' || s[j - 1] == '\t' || s[j - 1] == '\n'))
		j --;
	len = j - i;
	if (len < 0)
		len = 0;
	str = ft_strsub(&s[i], 0, len);
	return (str);
}
