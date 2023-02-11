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

static int	can_add_to_queue(t_queue *queue, t_flowmap *flowmap,
		t_room *link_to)
{
	int	ret;

	ret = 1;
	ret &= flow_allows_room_movement(flowmap, link_to);
	ret &= !bitmask_check_idx(&queue->rooms_used, link_to->number);
	return (ret);
}

static t_path	*bfs(t_queue *queue, t_flowmap *flowmap, t_info *info)
{
	t_queueitem *current_item;
	t_link		*current_link;
	static int	i;

	while (i < queue->top)
	{
		current_item = &queue->arr[i++];
		current_link = current_item->room->link_head;
		while (current_link != NULL)
		{
			if (current_link->link_to == info->end)
				return (path_find_next(info, current_item));
			if (!can_add_to_queue(queue, flowmap, current_link->link_to))
				continue ;
			if (bitmask_check_idx(&flowmap->open, current_link->number))
			{
			}
		}
	}
	return (0);
}

int	solve(t_info *info)
{	
	static t_queue	queue;
	t_pathgroup		*groups;
	t_flowmap		*flowmap;
	t_path			*next_path;

	groups = get_groups();
	flowmap = get_flowmap();
	queue_open(&queue, info->start);
	while (info->total_paths < info->ants * 2)
	{
		next_path = bfs(&queue, flowmap, info);
		if (!next_path)
			break ;
		else
			pathgroup_place_path(info, next_path, groups);
	}
	return (info->total_groups);
}
