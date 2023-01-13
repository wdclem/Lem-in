/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ants.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccariou <ccariou@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 12:43:53 by ccariou           #+#    #+#             */
/*   Updated: 2022/12/30 18:31:29 by ccariou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int	save_ants(t_info *info, int i)
{
	if (info->str[i] && !ft_strchr(info->str[i], (int) ' '))
	{
		i += check_comment(info, i);
		info->ants = ft_atoi(info->str[i]);
	}
	if (info->ants <= 0 || info->ants > ANTS_MAX)
		return(ERROR);
	else
		return (i + 1);
}
