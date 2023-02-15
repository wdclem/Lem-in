/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rooms.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccariou <ccariou@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 11:34:27 by ccariou           #+#    #+#             */
/*   Updated: 2023/02/15 19:00:15 by ccariou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

/* Create a new room in the HT
 * TODO check if coordinate needed/ t_coord ?
 */

static int	room_to_hasht(t_info *info, t_hasht *table
		, char **room_checker)
{
	if (set_table(info, table, room_checker[0]) != 0)
		return (ERROR);
/*	while (room_checker[++j])
		free(room_checker[j]);
	free(room_checker);
	room_checker = NULL;*/
	return (0);
}

int	validate_room_input(char **room_checker)
{
	int	split;
	int	str_idx;

	split = 0;
	str_idx = -1;
	while (room_checker[split] != NULL)
		split++;
	if (split != 3)
		return (ERROR);
	while (room_checker[1][str_idx++])
	{
		if (ft_isdigit(room_checker[1][str_idx]) != 1)
			return (ERROR);
	}
	str_idx = -1;
	while (room_checker[2][str_idx++])
	{
		if (ft_isdigit(room_checker[2][str_idx]) != 1)
			return (ERROR);
	}
	return (0);
}

int	unique_id(int id, t_hasht *table, char *room_name)
{
	if (table->room[id] != NULL && \
		ft_strcmp(table->room[id]->id, room_name) == 0)
		return (ERROR);
	else
		return (0);
}

int	room_is_valid(t_info *info, t_hasht *table, int i)
{
	char	**room_checker;

	room_checker = ft_strsplit(info->str[i], ' ');
	if (!room_checker)
		return (ERROR);
	if (validate_room_input(room_checker) == -1)
		return (ERROR);
	if (ft_atoi(room_checker[1]) < 0 || ft_atoi(room_checker[2]) < 0)
		return (ERROR);
	if (room_to_hasht(info, table, room_checker) != 0)
		return (ERROR);
	ft_freearray((void **)room_checker, 3);
	return (0);
}

int	save_rooms(t_info *info, t_hasht *table, int i)
{
	while (i < info->total_strs && !ft_strchr(info->str[i], '-'))
	{
		if (info->str[i][0] == 'L' || info->str[i][0] == 0)
			return (ERROR);
		else if (info->str[i][0] == '#')
		{
			if (check_comment_for_start_and_end(info, i) == -1)
				return (ERROR);
		}
		else if (ft_strchr(info->str[i], ' '))
		{
			if (room_is_valid(info, table, i) == 0)
				info->rooms += 1;
			else
				return (ERROR);
		}
		i++;
	}
	if (info->s_check != 1 || info->e_check != 1)
		return (ERROR);
	return (i);
}
