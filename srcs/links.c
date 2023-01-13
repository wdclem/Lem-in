/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   links.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccariou <ccariou@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 15:19:43 by ccariou           #+#    #+#             */
/*   Updated: 2023/01/06 04:03:25 by ccariou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"
/*
** add link to the link list of the room
** @src: pointer to the edge's source vertex
** @to: pointer to the edge's sink vertex
*/

static int	link_edge(t_room *from, t_room *link_to)
{
	t_link	*link;

	link = from->link;
	if (link != NULL)
	{
		while (link->next != NULL)
		{
			link = link->next;
		}
		link->next= new_link(from, link_to);
	}
	else
		from->link= new_link(from, link_to);	
/*	if (link)
	{
		while (link->next_adjacent)
		{
			link = link->next_adjacent;
		}
		link->next_adjacent = new_link(from, link_to);
		printf("from link = %s\n", link->from->id);
		printf("link to link = %s\n", link->link_to->id);
		if (!link->next_adjacent)
			return (ERROR);
	}
	else
	{
		if (from->link)
		{
			from->link = new_link(from, link_to);
			printf("from link = %s\n", link->from->id);
			printf("from link = %s\n", link->link_to->id);
		}
		else
			return (ERROR);
	}*/
	return (0);
}

/* return pointer to room if room exists */
t_room *pointer_to_room(t_hasht *table, char *id)
{
	t_room	*room;
	int		j;

	j  = 0;
	if (!id)
		return (NULL); // TODO cant return ERROR (int 1 ) sicne returning pointer so need to put error check in previous func
	j = dj2b_hash(id);
	room = table->room[j];
	while (room)
	{
		if (ft_strcmp(id, room->id) == 0)
		{
			room->link_count += 1;
			return (room);
		}
		else
			room = room->next;
	}
	return (NULL);
}

int	check_link(t_info *info, t_hasht *table, int i)
{
	char	**link;
	t_room	*from;
	t_room	*link_to;
	int		j;

	link = ft_strsplit(info->str[i], '-');
//	printf("link[0] == %s, link[1] == %s\n", link[0], link[1]);
	if (!link)
		return (ERROR);
	j = 0;
	while(link[j])
		j++;
	//TODO Maybe check for more error possibilities in here ? 
	if (j != 2 || ft_strcmp(link[0], link[1]) == 0)
		return(ERROR);
	else if(link[0] && link[1])
	{
		from = pointer_to_room(table, link[0]);
		link_to  = pointer_to_room(table, link[1]);
//		printf("from link = %s\n", from->id);
//		printf("link to = %s\n", link_to->id);
		if (!from || !link_to)
			return (ERROR);
		link_edge(from, link_to);
		link_edge(link_to, from);
		//TODO left here, link the two link both way together verify it works TODO TODO TODO
	}
	//TODO free 2d from printf on **link
	return (0);
}

int	save_links(t_info *info, t_hasht *table, int i)
{
//	link_key1 = 0;
//	link_key2= 0;
	printf("****LINKS****\ninfo->str[%d] == %s\n", i, info->str[i]);
	while (info->str[i] && (ft_strchr(info->str[i], '-') || info->str[i][0] == '#'))
	{
		if (info->str[i][0] == '#') 
			i = check_comment(info, i);
		if (info->str[i][0] != '#' && ft_strchr(info->str[i], '-'))
		{
			if(!check_link(info, table, i))
			{
					info->total_links += 1;
					i++;
			}
			else
				return (0); // No more room to read
		}
	}
	i = 0;
	printf("link count = %d\n", info->start->link_count);
/*	while (i < info->start->link_count)
	{
		printf("start link[%d] = %s\n", i, info->start->link->link_to->id);
		info->start->link = info->start->link->next_adjacent;
		i++;
	}
	*/
	printf("total link = %d\n", info->total_links);
//	free link
	return (0);
//	name_check = link_names(info);
//	if (i == 2 && 
	//FREE **LINK
}
