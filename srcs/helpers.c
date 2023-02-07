/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccariou <ccariou@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 13:33:00 by ccariou           #+#    #+#             */
/*   Updated: 2023/02/04 14:37:16 by ccariou          ###   ########.fr       */
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

t_link	*new_link(t_room *from, t_room *link_to)
{
	t_link	*link;

	link = (t_link *)malloc(sizeof(t_link));
	if (!link)
		return (NULL);
	link->from = from;
	link->link_to = link_to;
	link->flow = 0;
	link->next = NULL;
	return (link);
}

t_room	*make_room(t_info *info, char *key, int x, int y)
{
	t_room	*room;

	room = (t_room *)malloc(sizeof(t_room));
	if (!room)
		return (NULL);
	room->id = ft_strdup(key);
	room->number = info->rooms;
	room->x = x;
	room->y = y;
	room->visited = 0;
	room->valid = 0;
	room->occupied = 0;
	room->link_head = NULL;
	room->next = NULL;
	return (room);
}
