/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccariou <ccariou@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 13:33:00 by ccariou           #+#    #+#             */
/*   Updated: 2023/02/09 14:09:03 by ccariou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"
#include <stdint.h>

int	dj2b_hash(char *key)
{
	size_t			i;
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
	if (info->s_check == 1)
	{
		info->start = table->room[i];
		info->s_check = 0;
	}
	else if (info->e_check == 1)
	{
		info->end = table->room[i];
		info->e_check = 0;
	}
}

int	set_table(t_info *info, t_hasht *table, char *room_key)
{
	int		i;
	t_room	*new_room;

	i = dj2b_hash(room_key);
	while (table->room[i])
	{
		i++;
		if (i >= HT_CAP)
			i = 0;
	}
	new_room = table->room[i];
	if (!new_room)
	{
		table->room[i] = make_room(info, room_key);
	}
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
		info->s_check = 1;
		ret = 1;
	}
	else if (ft_strequ(info->str[i], "##end"))
	{
		info->e_check = 1;
		ret = 1;
	}
	return (ret);
}
