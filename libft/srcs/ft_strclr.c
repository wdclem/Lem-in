/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strclr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccariou <ccariou@hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 15:23:43 by ccariou           #+#    #+#             */
/*   Updated: 2022/09/09 11:52:10 by ccariou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"
/* sets every char of a string to the value \0
 */

void	ft_strclr(char *s)
{
	if (s != NULL)
	{
		while (*s)
		{
			*s = '\0';
			s ++;
		}
	}
}
