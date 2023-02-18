/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ants.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccariou <ccariou@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 12:43:53 by ccariou           #+#    #+#             */
/*   Updated: 2023/02/13 17:10:22 by ccariou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static int	validate_ant_count(t_info *info, int i)
{
	int	error_index;

	if (info->str[i][0] == '#')
	{
		if (check_comment_for_start_and_end(info, i))
			return (ERROR);
		else
			return (0);
	}
	else if (info->str[i] && !ft_strchr(info->str[i], (int) ' '))
	{
		error_index = 0;
		while (ft_isdigit(info->str[i][error_index]))
		{
			error_index++;
		}
		if (info->str[i][error_index])
			return (ERROR);
		return (1);
	}
	return (ERROR);
}

int	save_ants(t_info *info, int i)
{
	int	ants_found;

	ants_found = 0;
	while (i < info->total_strs && !ants_found)
	{
		ants_found = validate_ant_count(info, i);
		if (ants_found == -1)
			return (ERROR);
		else if (ants_found != 1)
			i++;
	}
	info->ants = ft_atoi(info->str[i]);
	if (info->ants <= 0 || info->ants > ANTS_MAX || info->str[i][0] == 0)
		return (ERROR);
	return (++i);
}
