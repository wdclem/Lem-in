/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccariou <ccariou@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 16:47:35 by ccariou           #+#    #+#             */
/*   Updated: 2023/02/07 12:22:25 by ccariou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"



static t_path	*bfs(t_queue *queue, t_flowmap *flowmap, t_info *info)
{
	t_queueitem *current_item;
	t_link		*current_link;
	t_room		*next_room;
	static int	i;

	while (i < queue->top)
	{
		current_item = &queue->arr[i++];
		current_link = current_item->room->link_head;
		while (current_link != NULL)
		{
			next_room = current_link->room_a;
			if (next_room == current_item->room)
				next_room = current_link->room_b;
			if (next_room == info->end)
				return (path_find_next(info, current_item));
			if (!queue_can_add_item(queue, flowmap, current_item->room, current_link))
				continue ;
			queue_add_item_and_update_flow(queue, flowmap, current_link, \
					next_room);
		}
	}
	return (0);
}

int	solve(t_info *info)
{	
	t_queue		*queue;
	t_pathgroup	*groups;
	t_flowmap	*working_flowmap;
	t_path		*next_path;

	queue = get_queue();
	groups = get_groups();
	working_flowmap = get_working_flowmap();
	while (queue_can_be_opened(queue, get_stable_flowmap(), info->start))
	{
		next_path = bfs(queue, working_flowmap, info);
		if (!next_path)
			break ;
		else
			pathgroup_place_path(info, next_path, groups);
	}
	return (info->total_groups);
}
