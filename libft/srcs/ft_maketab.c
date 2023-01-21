/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_maketab.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccariou <ccariou@hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 10:20:12 by ccariou           #+#    #+#             */
/*   Updated: 2022/09/09 11:52:00 by ccariou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	**ft_maketab(int len)
{
	char	**tab;

	tab = (char **)malloc(sizeof(char *) * (len + 1));
	if (tab == NULL)
	{
		return (NULL);
	}
	return (tab);
}
