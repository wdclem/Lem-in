/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccariou <ccariou@hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 20:27:53 by ccariou           #+#    #+#             */
/*   Updated: 2022/09/09 11:52:10 by ccariou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"
/* Function returns a pointer to a new string duplicate from string.
 * Malloc is used to get memory for the duplicata.
*/

char	*ft_strdup(const char *s1)
{
	int		len;
	int		i;
	char	*dest;

	i = 0;
	len = 0;
	while (s1[len])
		len++;
	dest = (char *)malloc(sizeof(char) * (len + 1));
	if (dest == NULL)
		return (NULL);
	while (s1[i] != '\0')
	{
		dest[i] = s1[i];
		i ++;
	}
	dest[i] = '\0';
	return (dest);
}
