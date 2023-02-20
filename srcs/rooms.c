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

static int	room_to_hasht(t_info *info, t_hasht *table, char **room_checker)
{
	if (set_table(info, table, room_checker[0]) != 0)
		return (ERROR);
	return (0);
}

int	validate_room_input(char **room_checker, int *split)
{
	while (room_checker[(*split)] != NULL)
		(*split)++;
	if (*split != 3)
		return (ERROR);
	if (validate_string_is_integer(room_checker[1]) == -1 || \
			validate_string_is_integer(room_checker[2]) == -1)
		return (ERROR);
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
	int		count;

	count = 0;
	if (count_amount_of_chars_in_str(info->str[i], ' ') != 2)
	{
		ft_printf("Line %d invalid: wrong amount of ` ` characters\n", i + 1);
		return (ERROR);
	}
	room_checker = ft_strsplit(info->str[i], ' ');
	if (!room_checker)
		return (ERROR);
	if (validate_room_input(room_checker, &count) == -1)
		return (free_str_split(room_checker, count, ERROR));
	if (count_amount_of_chars_in_str(room_checker[0], '-') != 0)
	{
		ft_printf("Line %d invalid: Character `-` not allowed in room name\n", \
				i + 1);
		return (free_str_split(room_checker, count, ERROR));
	}
	if (room_to_hasht(info, table, room_checker) != 0)
		return (free_str_split(room_checker, count, ERROR));
	ft_freearray((void ***)&room_checker, count);
	return (0);
}

int	save_rooms(t_info *info, t_hasht *table, int i)
{
	while (info->str[i] && i < info->total_strs && \
			(ft_strchr(info->str[i], ' ') || ft_strchr(info->str[i], '#')))
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
	if (info->start == NULL || info->end == NULL)
		return (ERROR);
	return (i);
}
