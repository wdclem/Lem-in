/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccariou <ccariou@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 13:33:00 by ccariou           #+#    #+#             */
/*   Updated: 2023/01/14 14:09:38 by ccariou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

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

int	check_comment(t_info *info, int i)
{
	while (info->str[i][0] == '#')
	{
		if (ft_strequ(info->str[i], "##start"))
		{
			info->s_check = 1;
			i++;
			return (i);
		}
		else if (ft_strequ(info->str[i], "##end"))
		{
			info->e_check = 1;
			i++;
			return (i);
		}
		else
			i++;
	}
	return (i);
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

t_room	*make_room(char *key, int x, int y)
{
	t_room	*room;

	room = (t_room *)malloc(sizeof(t_room));
	if (!room)
		return (NULL);
	room->id = ft_strdup(key);
	room->x = x;
	room->y = y;
	room->visited = 0;
	room->valid = 0;
	room->link_head = NULL;
	room->next = NULL;
	return (room);
}
