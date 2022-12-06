/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccariou <ccariou@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 13:10:26 by ccariou           #+#    #+#             */
/*   Updated: 2022/12/06 13:29:27 by ccariou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

/*
int	error_management(t_info *info, int error_code)
{}
*/
int	check_comment(t_info *info, int i)
{
	while (info->str[i][0] == '#')
	{
		if (ft_strcmp(info->str[i], "##start") == 0)
			info->start = i;
		else if (ft_strcmp(info->str[i], "##end") == 0)
			info->end = i;
		i++;
	}
	return (i);
}
