/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccariou <ccariou@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 13:33:00 by ccariou           #+#    #+#             */
/*   Updated: 2023/02/13 19:24:01 by ccariou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"
#include <stdint.h>

int	dj2b_hash(char *key)
{
	int				i;
	unsigned long	hash;

	i = 0;
	hash = 5381;
	while (key[i] != '\0')
	{
		hash = (((hash << 5) + hash) + key[i]) % HT_CAP;
		i++;
	}
	return (hash);
}

static void	set_start_end(t_info *info, t_hasht *table, int i)
{
	if (info->s_check == 1 && !info->start)
		info->start = table->room[i];
	else if (info->e_check == 1 && !info->end)
		info->end = table->room[i];
}

int	set_table(t_info *info, t_hasht *table, char *room_key)
{
	int		i;
	t_room	*new_room;

	i = dj2b_hash(room_key);
	//dprintf(2, "table i == %d\n", i);
	//if (unique_id(i, table, room_key) != 0)
	//	return (ERROR);
	while (table->room[i])
	{
		if (unique_id(i, table, room_key) != 0)
			return (ERROR);
		i++;
		if (i >= HT_CAP)
			i = 0;
	}
	new_room = table->room[i];
	if (!new_room)
	{
		table->room[i] = make_room(info, room_key);
		if (table->room[i] == NULL)
			return	(ERROR);
	}
	if (!info->start || !info->end)
		set_start_end(info, table, i);
	while (new_room != NULL)
	{
		if (!ft_strequ(room_key, new_room->id))
			return (ERROR);
	}
	return (0);
}

int	check_comment_for_start_and_end(t_info *info, int i)
{
	int	ret;

	ret = 0;
	if (ft_strequ(info->str[i], "##start"))
	{
		if ((info->str[i + 1] && info->str[i + 1][0] == '#') || (info->str[i + 1] && ft_strchr(info->str[i + 1], '-')))
			return (-1);
		else if (info->str[i + 1] && info->str[i + 1][0] == 0)
			return (-1);
		info->s_check += 1;
		ret = 1;
	}
	else if (ft_strequ(info->str[i], "##end"))
	{
		if ((info->str[i + 1] && info->str[i + 1][0] == '#') || (info->str[i + 1] && ft_strchr(info->str[i + 1], '-')))
			return (-1);
		else if (info->str[i + 1] && info->str[i + 1][0] == '0') 
			return (-1);
		info->e_check += 1;
		ret = 1;
	}
	return (ret);
}
