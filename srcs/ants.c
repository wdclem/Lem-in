/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ants.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccariou <ccariou@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 12:43:53 by ccariou           #+#    #+#             */
/*   Updated: 2023/01/14 13:39:01 by ccariou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int	save_ants(t_info *info, int i, int *error)
{
	if (info->str[i] && !ft_strchr(info->str[i], (int) ' '))
	{
		info->ants = ft_atoi(info->str[i]);
		return (1);
	}
	if (info->ants <= 0 || info->ants > ANTS_MAX)
	{
		*error = 1;
		return (-1);
	}
	else
		return (0);
}
