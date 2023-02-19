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

int	save_ants(t_info *info, int i)
{
	if (validate_string_is_integer(info->str[i]) == -1)
		return (ERROR);
	info->ants = ft_atoi(info->str[i]);
	if (info->ants <= 0 || info->ants > ANTS_MAX || info->str[i][0] == 0)
		return (ERROR);
	return (++i);
}
