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

int	save_map(t_info *info)
{
	char	*line;
	int		i;
	int		len;
	int		gnl_ret;

	line = NULL;
	i = -1;
	len = 50000;
	gnl_ret = 1;
	info->str = (char **)malloc(sizeof(char *) * len + 1);
	if (!info->str)
		return (ERROR);
	while (gnl_ret && i++ < len)
	{
		gnl_ret = get_next_line(0, &line);
		if (gnl_ret == 0)
		{
			if (i == 0)
				return (ERROR);
			break ;
		}
		if (gnl_ret < 0)
			return (ERROR);
		info->str[i] = line;
		if (info->str[i] == NULL)
			return (ERROR);
	}
	info->total_strs = i;
	free(line);
	return (0);
}
