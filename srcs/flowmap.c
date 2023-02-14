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

const char *flow_to_str(t_flowmask flow)
{
	const char	*strs[] = {
		"Open",
		"UPSTREAM",
		"DOWNSTREAM",
		"",
		"Blocked"
	};

	return (strs[(int)flow]);
}

void	flowmap_debug_print(t_flowmap *flowmap, int count)
{
	for (int i = 0; i < count; i++)
	{
		dprintf(2, "Link %d: %s\n", i, flow_to_str(flowmap->arr[i]));
	}
}

static int	can_flow_towards(t_queue *queue, t_flowmap *stable_flowmap, \
		t_flowmap *working_flowmap, t_link *link_to_follow)
{

	const t_flowmask	stable_flow = \
								stable_flowmap->arr[link_to_follow->number];
	const t_flowmask	working_flow = \
								working_flowmap->arr[link_to_follow->number];
	int					ret;

	(void) working_flow;
	ret = !bitmask_check_idx(&queue->rooms_used, link_to_follow->link_to->number);
//	ret &= !bitmask_check_idx(&queue->path_rooms_used, link_to_follow->link_to->number);
	ret &= stable_flow == DOWNSTREAM;
	return (ret);
}

void	flowmap_update_stable_map(t_queueitem *sink, t_flowmap *working, \
			t_flowmap *stable, int total_links)
{
	t_queueitem	*seek;
	int			link_number;
	int			pair_number;

	dprintf(2, "Update: working flowmap at this point in time:\n");
		flowmap_debug_print(working, total_links);
	seek = sink;
	while (seek->previous_item != NULL)
	{
		link_number = seek->link_used->number;
		pair_number = link_number + 
			(link_number % 2 == 0) - (link_number % 2 == 1);
		if (stable->arr[link_number] != OPEN && 
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
	dprintf(2, "Stable flowmap at this point in time:\n");
	flowmap_debug_print(stable, total_links);
	dprintf(2, "\n");
}

t_path	*flowmap_paths_remain(t_queue *queue, t_flowmap *stable_flowmap, \
		t_info *info, int *i)
{
	t_queueitem	*current_item;
	t_link		*current_link;
	t_room		*next_room;
	t_flowmap	*working_flowmap;
	
	working_flowmap = get_working_flowmap();
	while (*i < queue->top)
	{
		current_item = &queue->arr[(*i)++];
		current_link = current_item->room->link_head;
		while (current_link != NULL)
		{
			next_room = current_link->link_to;
			if (next_room == info->start)
				return (path_make_next(info, current_item));
			if (can_flow_towards(queue, stable_flowmap, working_flowmap, \
						current_link))
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

static inline t_link	*find_link_to_previous_room(t_room *previous_room, t_room *current_room)
{
	t_link	*forced_link;
	
	forced_link = current_room->link_head;
	while (forced_link->link_to != previous_room)
		forced_link = forced_link->next;
	return (forced_link);
}

int	flowmap_forces_movement(t_queue *queue, t_info *info, t_queueitem *current_item)
{
	t_path		*path_arr;
	t_path		*current_path;
	t_link		*forced_link;
	t_room		*previous_room_on_path;
	t_flowmap	*working_flowmap;

	path_arr = get_path_arr();
	current_path = path_arr;
	working_flowmap = get_working_flowmap();
	while (current_path < path_arr + info->total_paths)
	{
		if (bitmask_check_idx(&current_path->rooms_used, current_item->room->number))
		{
			previous_room_on_path = find_previous_room(current_path, current_item->room);
			if (!previous_room_on_path || previous_room_on_path == info->start)
				return (1);
			forced_link = find_link_to_previous_room(previous_room_on_path, current_item->room);
			queue_add_item_and_update_flow(queue, working_flowmap, forced_link, current_item);
			(&queue->arr[queue->top - 1])->was_forced_to_move = 1;
			return (1);
		}
		current_path++;
	}
	return (0);
}
