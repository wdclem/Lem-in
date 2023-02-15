/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccariou <ccariou@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 17:58:04 by ccariou           #+#    #+#             */
/*   Updated: 2023/02/09 14:14:53 by ccariou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

t_ant	*init_ant(t_info *info, int *id)
{
	t_ant	*ant;

	ant = (t_ant *)ft_memalloc(sizeof(t_ant));
	ant->room = info->start;
	ant->id = (*id)++;
	return (ant);
}

t_ant	**ants_array(t_info *info, t_ant **array)
{
	int		i;
	int		id;

	i = 0;
	id = 1;
	while (i < info->ants)
	{
		array[i] = init_ant(info, &id);
		i++;
	}
	return (array);
}

t_hasht	*table_init(void)
{
	t_hasht		*table;

	table = (t_hasht *)malloc(sizeof(t_hasht));
	if (!table)
		return (NULL);
	table->room = (t_room **)ft_memalloc(sizeof(t_room *) * HT_CAP);
	if (!table->room)
		return (NULL);
	ft_bzero(table->room, HT_CAP);
	return (table);
}

t_link	*new_link(t_room *from, t_room *link_to)
{
	t_link					*link;
	static unsigned short	number;

	link = (t_link *)ft_memalloc(sizeof(t_link));
	if (!link)
		return (NULL);
	link->number = number++;
	link->from = from;
	link->link_to = link_to;
	link->next = NULL;
	return (link);
}

t_room	*make_room(t_info *info, char *key)
{
	t_room	*room;

	room = (t_room *)ft_memalloc(sizeof(t_room));
	if (!room)
		return (NULL);
	room->id = ft_strdup(key);
	room->number = info->rooms;
	room->valid = 0;
	room->occupied = 0;
	room->link_head = NULL;
	return (room);
}
