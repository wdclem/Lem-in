/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   links.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccariou <ccariou@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 15:19:43 by ccariou           #+#    #+#             */
/*   Updated: 2023/02/13 17:31:16 by ccariou          ###   ########.fr       */
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
			link = link->next;
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
		return (NULL);
	j = dj2b_hash(id);
	while (ft_strcmp(table->room[j]->id, id) != 0)
	{
		j++;
		if (j >= HT_CAP)
			j = 0;
	}
	room = table->room[j];
	if (room == NULL)
		return (NULL);
	room->link_count += 1;
	return (room);
}

int	link_room_exist(t_hasht *table, char *from, char *link_to)
{
	int hash_from;
	int hash_to;

	hash_from = 0;
	hash_to = 0;
	if (!from || !link_to || !table)
		return (ERROR);
	hash_from  = dj2b_hash(from);
	hash_to = dj2b_hash(link_to);
	if (!table->room[hash_from] || !table->room[hash_to])
		return (ERROR);
	if (ft_strcmp(table->room[hash_from]->id, from) != 0 || ft_strcmp(table->room[hash_to]->id, link_to) != 0)
		return (ERROR);
	return (0);
}	

int	check_link(t_info *info, t_hasht *table, int i)
{
	char	**link;
	t_room	*from;
	t_room	*link_to;
	int		room_idx;
	int		j;
	t_link	*next_link;

	link = ft_strsplit(info->str[i], '-');
//	printf("link[0] == %s, link[1] == %s\n", link[0], link[1]);
	if (!link)
		return (ERROR);
	room_idx = dj2b_hash(link[0]);
	j = 0;
	while (link[j])
		j++;
	if (j != 2 || ft_strcmp(link[0], link[1]) == 0)
		return (ERROR);
//	if (link_room_exist(table, link[0], link[1]) != 0)
//		return (ERROR);
	next_link = table->room[room_idx]->link_head;
	while (next_link)
	{
		if (ft_strcmp(next_link->link_to->id, link[1]) == 0)
			return (ERROR);
		else
			next_link = next_link->next;
	}
	if (link[0] && link[1])
	{
		from = pointer_to_room(table, link[0]);
		link_to = pointer_to_room(table, link[1]);
		if (!from || !link_to)
			return (ERROR);
		add_link(from, link_to);
		add_link(link_to, from);
	}
	return (0);
}

int	save_links(t_info *info, t_hasht *table, int i)
{
	while (i < info->total_strs && info->str[i]) //&& !ft_strchr(info->str[i], ' '))
	{
		if(ft_strchr(info->str[i], '-') && info->str[i][0] == '#' && info->str[i][1] != '#')
			i++;
		if (info->str[i][0] == 0 || (!ft_strchr(info->str[i], '-') && info->str[i][0] != '#') || (info->str[i][0] != '#' && ft_strchr(info->str[i], '#')))//(ft_strchr(info->str[i], '-') && ft_strchr(info->str[i], '#')))
			return (ERROR);
		if (info->str[i][0] == '#')
		{
			if (check_comment_for_start_and_end(info, i) == -1)
				return (ERROR);
		}
		else if (ft_strchr(info->str[i], '-'))
		{
			if (!check_link(info, table, i))
				info->total_links += 2;
			else
				return(ERROR);
		}
		i++;
	}	//printf("link count = %d\n", info->start->link_count);
	if (info->total_links == 0)
		return(ERROR);
//	printf("total link = %d\n", info->total_links);
	return (0);
}
