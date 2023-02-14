/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpolonen <tpolonen@student.hive.fi>          +#+  +:+       +#+      */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 14:59:25 by tpolonen           #+#    #+#            */
/*   Updated: 2023/01/16 18:30:07 by tpolonen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int	queue_can_add_room(t_queue *queue, t_flowmap *stable_flowmap, \
		t_link *link_to_follow)
{
	const t_flowmask	current_flow = \
								stable_flowmap->arr[link_to_follow->number];
	int					ret;

	ret = !bitmask_check_idx(&queue->rooms_used, link_to_follow->link_to->number);
//	ret &= !bitmask_check_idx(&queue->path_rooms_used, link_to_follow->link_to->number);
	ret &= current_flow == OPEN;
	return (ret);
}

void	queue_add_item_and_update_flow(t_queue *queue, t_flowmap *flowmap,
		t_link *link_to_follow, t_queueitem *previous)
{
	t_flowmask	*workflow_forward;
	t_flowmask	*workflow_backward;
	t_flowmask	*stableflow_forward;
	t_flowmask	*stableflow_backward;
	t_room		*room_to_go;

	t_flowmap *stablemap = get_stable_flowmap();
	workflow_forward = &flowmap->arr[link_to_follow->number];
	workflow_backward = &flowmap->arr[link_to_follow->number + 
			(link_to_follow->number % 2 == 0) - (link_to_follow->number % 2 == 1)];
	stableflow_forward = &stablemap->arr[link_to_follow->number];
	stableflow_backward = &stablemap->arr[link_to_follow->number + 
			(link_to_follow->number % 2 == 0) - (link_to_follow->number % 2 == 1)];
	dprintf(2, "Exploring link %d/%d, from:%s link_to:%s\n", link_to_follow->number,
			link_to_follow->number + (link_to_follow->number % 2 == 0) - (link_to_follow->number % 2 == 1), link_to_follow->from->id, link_to_follow->link_to->id);
	dprintf(2, "Stable:  Forward %12s Backward %12s ->\n", flow_to_str(*stableflow_forward), \
			flow_to_str(*stableflow_backward));
	*workflow_forward = UPSTREAM;
	*workflow_backward = DOWNSTREAM;
	dprintf(2, "Working: Forward %12s Backward %12s\n\n", flow_to_str(*workflow_forward), \
			flow_to_str(*workflow_backward));
	room_to_go = link_to_follow->link_to;
	queue_add_item(&queue, room_to_go, link_to_follow, previous);
}

void queue_add_item(t_queue **queue, t_room *next_room, \
		t_link *link_used, t_queueitem *previous)
{
	t_queueitem *new_item;

	new_item = (*queue)->arr + (*queue)->top;
	new_item->room = next_room;
	new_item->previous_item = previous;
	new_item->link_used = link_used;
	if (previous)
		new_item->steps = previous->steps + 1;
	bitmask_set_idx(&(*queue)->rooms_used, next_room->number);
	(*queue)->top++;
}

int	queue_can_be_opened(t_queue *queue, t_flowmap *stable_flowmap, \
		t_info *info)
{
	t_flowmap			*working_flowmap;
	t_link				*next_link;

	working_flowmap = get_working_flowmap();
	queue_clear(&queue);
	queue_add_item(&queue, info->start, NULL, NULL);
	ft_bzero((void *)&working_flowmap->arr, \
			sizeof(t_flowmask) * info->total_links);
	next_link = info->start->link_head;
	while (next_link)
	{
		if (queue_can_add_room(queue, stable_flowmap, next_link))
			queue_add_item_and_update_flow(queue, working_flowmap, \
					next_link, (t_queueitem *)&queue->arr[0]);
		next_link = next_link->next;
	}
	return (queue->top > 1);
}

void queue_clear(t_queue **queue)
{
	ft_bzero((void *)(*queue)->arr, sizeof(t_queueitem) * (*queue)->top);
	bitmask_clear(&(*queue)->rooms_used);
	(*queue)->top = 0;
}
