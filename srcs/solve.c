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

static int	add_to_queue_and_update_flow(t_queue *queue, t_flowmap *flowmap,
		t_link *link_to_follow, t_room *room_to_go)
{
	t_flowmask	*current_flow;

	current_flow = &flowmap->arr[link_to_follow->number];
	if (room_to_go == link_to_follow->room_a)
	{
		if (*current_flow == A_TO_B)
			*current_flow = BLOCKED;
		else
			*current_flow = B_TO_A;
	}
	else
	{
		if (*current_flow == B_TO_A)
			*current_flow = BLOCKED;
		else
			*current_flow = A_TO_B;
	}
	queue_add_item(&queue, link_to_follow, room_to_go);
	return (0);
}

static int	can_add_to_queue(t_flowmap *flowmap, t_room *source, t_link *link_to_follow)
{
	int	ret;

	ret = 1;
	ret &= flow_allows_room_movement(flowmap, source, link_to_follow);
	return (ret);
}

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
			if (!can_add_to_queue(flowmap, current_item->room, current_link))
				continue ;
			add_to_queue_and_update_flow(queue, flowmap, current_link, \
					next_room);
		}
	}
	return (0);
}

int	solve(t_info *info)
{	
	static t_queue	queue;
	t_pathgroup		*groups;
	t_flowmap		*working_flowmap;
	t_flowmap		*stable_flowmap;
	t_path			*next_path;

	groups = get_groups();
	working_flowmap = get_working_flowmap();
	queue_open(&queue, info->start);
	while (info->total_paths < info->ants * 2)
	{
		next_path = bfs(&queue, working_flowmap, info);
		if (!next_path)
			break ;
		else
			pathgroup_place_path(info, next_path, groups);
	}
	return (info->total_groups);
}
