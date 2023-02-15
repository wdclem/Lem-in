/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flowmap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccariou <ccariou@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 16:47:35 by ccariou           #+#    #+#             */
/*   Updated: 2023/02/07 12:22:25 by ccariou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	flowmap_update_stable_map(t_queueitem *sink, t_flowmap *working, \
			t_flowmap *stable)
{
	t_queueitem	*seek;
	int			link_number;
	int			pair_number;

	seek = sink;
	while (seek->previous_item != NULL)
	{
		link_number = seek->link_used->number;
		pair_number = link_number + \
			(link_number % 2 == 0) - (link_number % 2 == 1);
		if (stable->arr[link_number] != OPEN && \
			stable->arr[link_number] != working->arr[link_number])
		{
			*(&stable->arr[link_number]) = BLOCKED;
			*(&stable->arr[pair_number]) = BLOCKED;
		}
		else
		{
			*(&stable->arr[link_number]) = working->arr[link_number];
			*(&stable->arr[pair_number]) = working->arr[pair_number];
		}
		seek = seek->previous_item;
	}
}

t_path	*flowmap_paths_remain(t_queue *queue, t_flowmap *stable_flowmap, \
		t_info *info, int *i)
{
	t_queueitem	*current_item;
	t_link		*current_link;
	t_room		*next_room;

	while (*i < queue->top)
	{
		current_item = &queue->arr[(*i)++];
		current_link = current_item->room->link_head;
		while (current_link != NULL)
		{
			next_room = current_link->link_to;
			if (next_room == info->start)
				return (path_make_next(info, current_item));
			if (queue_can_add_room(queue, stable_flowmap, current_link, \
						DOWNSTREAM))
			{
				queue_add_item(&queue, next_room, current_link, current_item);
			}
			current_link = current_link->next;
		}
	}
	return (NULL);
}

static inline t_room	*find_previous_room(t_path *path, t_room *current_room)
{
	int		path_idx;

	path_idx = 0;
	while (path_idx < path->len - 1)
	{
		if (path->room_arr[path_idx + 1] == current_room)
		{
			return (path->room_arr[path_idx]);
		}
		path_idx++;
	}
	return (NULL);
}

static inline t_link	*find_link_to_previous_room(t_room *previous_room, \
		t_room *current_room)
{
	t_link	*forced_link;

	forced_link = current_room->link_head;
	while (forced_link->link_to != previous_room)
		forced_link = forced_link->next;
	return (forced_link);
}

int	flowmap_forces_movement(t_queue *queue, t_info *info, t_queueitem *item)
{
	t_path		*path_arr;
	t_path		*path;
	t_link		*link;
	t_room		*previous_room;
	t_flowmap	*flowmap;

	path_arr = get_path_arr();
	path = path_arr;
	flowmap = get_working_flowmap();
	while (path < path_arr + info->total_paths)
	{
		if (bitmask_check_idx(&path->rooms_used, item->room->number))
		{
			previous_room = find_previous_room(path, item->room);
			if (!previous_room || previous_room == info->start)
				return (1);
			link = find_link_to_previous_room(previous_room, item->room);
			queue_add_item_and_update_flow(queue, flowmap, link, item);
			(&queue->arr[queue->top - 1])->was_forced_to_move = 1;
			return (1);
		}
		path++;
	}
	return (0);
}
