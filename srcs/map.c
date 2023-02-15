/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccariou <ccariou@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 15:15:13 by ccariou           #+#    #+#             */
/*   Updated: 2023/02/15 19:47:58 by ccariou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static int	can_read_map(t_info *info, int i)
{
	int		gnl_ret;

	gnl_ret = get_next_line(0, &info->str[i]);
	if (gnl_ret == 0)
	{
		if (i == 0)
			return (ERROR);
		return (gnl_ret);
	}
	if (gnl_ret < 0)
		return (ERROR);
	if (info->str[i] == NULL)
		return (ERROR);
	return (gnl_ret);
}

int	save_map(t_info *info)
{
	const int	len = 50000;
	int			gnl_ret;
	int			i;

	info->str = (char **)ft_memalloc(sizeof(char *) * len + 1);
	if (!info->str)
		return (ERROR);
	i = 0;
	gnl_ret = 1;
	while (gnl_ret > 0 && i <= len - 1)
	{
		gnl_ret = can_read_map(info, i);
		i++;
	}
	info->total_strs = i;
	if (gnl_ret < 0)
		return (ERROR);
	return (0);
}
