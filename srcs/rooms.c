/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rooms.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccariou <ccariou@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 11:34:27 by ccariou           #+#    #+#             */
/*   Updated: 2023/02/09 14:10:06 by ccariou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

/* Create a new room in the HT
 * TODO check if coordinate needed/ t_coord ?
 */

static int	room_to_hasht(t_info *info, t_hasht *table, int i
		, char **room_checker)
{
	int		j;

	j = -1;
	set_table(info, table, room_checker[0]);
	while (room_checker[++j])
		free(room_checker[j]);
	free(room_checker);
	room_checker = NULL;
	return (i);
}

int	validate_room_input(char **room_checker)
{
	int	split;

	split = 0;
	while (room_checker[split] != NULL)
		split++;
	return (split);
}

int	unique_id(t_room *room, char **room_checker)
{
	int	i;

	i = 0;
	while (room->id[i])
	{
		if (!ft_strcmp(room->id, room_checker[0]))
			return (1);
		i++;
	}
	return (0);
}

int	room_is_valid(t_info *info, t_hasht *table, int i)
{
	char	**room_checker;

	room_checker = ft_strsplit(info->str[i], ' ');
	if (validate_room_input(room_checker) != 3)
		return (0);
	if (ft_atoi(room_checker[1]) < 0 || ft_atoi(room_checker[2]) < 0)
		return (0);
	room_to_hasht(info, table, i, room_checker);
	return (1);
}

int	save_rooms(t_info *info, t_hasht *table, int i, int *error)
{
	printf("*********ROOMS********\n");
	while (i < info->total_strs && !ft_strchr(info->str[i], '-') && !(*error))
	{
		if (info->str[i][0] == 'L')
			*error = 1;
		else if (info->str[i][0] == '#')
			check_comment_for_start_and_end(info, i);
		else if (ft_strchr(info->str[i], ' '))
		{
			if (room_is_valid(info, table, i) == 1)
				info->rooms += 1;
			else
				*error = 1;
		}
		i++;
	}
	if (!info->start || !info->end || *error)
		return (ERROR);
	return (i);
}
