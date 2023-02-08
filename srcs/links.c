/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   links.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccariou <ccariou@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 15:19:43 by ccariou           #+#    #+#             */
/*   Updated: 2023/01/14 14:12:54 by ccariou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"
/*
** add link to the link list of the room
*/

static int	add_link(t_room *from, t_room *link_to)
{
	t_link	*link;

	link = from->link_head;
	if (link != NULL)
	{
		while (link->next != NULL)
		{
			link = link->next;
		}
		link->next = new_link(from, link_to);
	}
	else
		from->link_head = new_link(from, link_to);
	return (0);
}

/* return pointer to room if room exists */
t_room	*pointer_to_room(t_hasht *table, char *id)
{
	t_room	*room;
	int		j;

	j = 0;
	if (!id)
		return (NULL); // TODO cant return ERROR (int 1 ) sicne returning pointer so need to put error check in previous func
	j = dj2b_hash(id);
	while (ft_strcmp(table->room[j]->id, id))
	{
		j++;
		if (j >= HT_CAP)
			j = 0;
	}
	room = table->room[j];
	room->link_count += 1;
	return (room);
}

int	check_link(t_info *info, t_hasht *table, int i)
{
	char	**link;
	t_room	*from;
	t_room	*link_to;
	int		j;

	link = ft_strsplit(info->str[i], '-');
	if (!link)
		return (ERROR);
	j = 0;
	while (link[j])
		j++;
	//TODO Maybe check for more error possibilities in here ? 
	if (j != 2 || ft_strcmp(link[0], link[1]) == 0)
		return (ERROR);
	else if (link[0] && link[1])
	{
		from = pointer_to_room(table, link[0]);
		link_to = pointer_to_room(table, link[1]);
		if (!from || !link_to)
			return (ERROR);
		add_link(from, link_to);
		add_link(link_to, from);
		//TODO left here, link the two link both way together verify it works TODO TODO TODO
	}
	//TODO free 2d from printf on **link
	return (0);
}

int	save_links(t_info *info, t_hasht *table, int i, int *error)
{
	printf("****LINKS****\ninfo->str[%d] == %s\n", i, info->str[i]);
	while (i < info->total_strs && !(*error))
	{
		if (info->str[i][0] == '#' && check_comment_for_start_and_end(info, i))
			*error = 1;
		if (!(*error) && ft_strchr(info->str[i], '-'))
		{
			if (!check_link(info, table, i))
				info->total_links += 1;
			else
				return (0); // No more room to read
		}
		i++;
	}
	printf("link count = %d\n", info->start->link_count);
	printf("total link = %d\n", info->total_links);
	return (*error);
	//FREE **LINK
}
