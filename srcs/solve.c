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

static int	can_add_to_queue(t_queue *queue, t_room *link_to)
{
	int	ret;

	ret = 1;
	ret &= flow_allows_movement(link_to->number);
	ret &= !check_bitmask_idx(&queue->rooms_used, link_to->number);
	return (ret);
}

static t_path	*bfs(t_queue *queue, t_info *info)
{
	t_queueitem *current_item;
	t_link		*current_link;
	static int	i;

	while (i >= 0 && i < queue->top)
	{
		current_item = &queue->arr[i++];
		if (flow_forces_movement(queue, current_item))
			continue ;
		current_link = current_item->room->link_head;
		while (current_link != NULL)
		{
			if (current_link->link_to == info->end)
				return (path_find_next(info, current_item));
			if (current_link->link_to != info->start &&
					can_add_to_queue(queue, current_link->link_to))
				queue_add_item(&queue, current_link, current_item);
			current_link = current_link->next;
		}
	}
	return (0);
}

int	solve(t_info *info)
{	
	static t_queue		queue;
	t_pathgroup	*groups;
	t_path		*next_path;

	groups = get_groups();
	queue_open(&queue, info->start);
	while (info->total_paths < info->ants * 2)
	{
		next_path = bfs(&queue, info);
		if (!next_path)
			break ;
		else
			pathgroup_place_path(info, next_path, groups);
	}
	return (info->total_groups);
}
