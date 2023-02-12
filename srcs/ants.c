/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ants.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccariou <ccariou@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 12:43:53 by ccariou           #+#    #+#             */
/*   Updated: 2023/02/12 12:43:12 by ccariou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int	save_ants(t_info *info, int i)
{
	int	error_index;

	error_index = 0;
	if (info->str[i] && !ft_strchr(info->str[i], (int) ' '))
	{
		while (ft_isdigit(info->str[i][error_index]))
		{
			if (!ft_isdigit(info->str[i][error_index]))
				return (error_center(2));
			else
				error_index++;	
		}
	}
	info->ants = ft_atoi(info->str[i]);
	if (info->ants <= 0 || info->ants > ANTS_MAX || info->str[i][0] == 0)
		return (error_center(2));
	return (1);
}
