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
		t_room *dst, t_link *link_to_follow)
{

	const t_flowmask	current_flow = \
								stable_flowmap->arr[link_to_follow->number];
	int					ret;

	ret = !bitmask_check_idx(&queue->rooms_used, dst->number);
	ret &= !bitmask_check_idx(&queue->path_rooms_used, dst->number);
	ret &= current_flow == DOWNSTREAM;
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
		*(&stable->arr[link_number]) = 
			*(&working->arr[link_number]);
		*(&stable->arr[pair_number]) = 
			*(&working->arr[pair_number]);
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
	
	while (*i < queue->top)
	{
		current_item = &queue->arr[(*i)++];
		current_link = current_item->room->link_head;
		while (current_link != NULL)
		{
			next_room = current_link->link_to;
			if (next_room == info->start)
				return (path_make_next(info, current_item));
			if (can_flow_towards(queue, stable_flowmap, next_room, \
						current_link))
			{
				queue_add_item(&queue, next_room, current_link, current_item);
			}
			current_link = current_link->next;
		}
	}
	return (NULL);
}
