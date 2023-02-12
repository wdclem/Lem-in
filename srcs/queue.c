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
		t_room *source, t_link *link_to_follow)
{
	const t_flowmask	current_flow = \
								stable_flowmap->arr[link_to_follow->number];
	int					ret;

	ret = bitmask_check_idx(&queue->rooms_used, source->number);
	ret &= current_flow != BLOCKED;
	ret &= link_to_follow->room_a == source && current_flow == A_TO_B;
	ret &= link_to_follow->room_b == source && current_flow == B_TO_A;
	return (ret);
}

void	queue_add_item_and_update_flow(t_queue *queue, t_flowmap *flowmap,
		t_link *link_to_follow, t_queueitem *previous)
{
	t_flowmask	*current_flow;
	t_room		*room_to_go;

	current_flow = &flowmap->arr[link_to_follow->number];
	if (previous->room == link_to_follow->room_a)
	{
		*current_flow = A_TO_B;
		room_to_go = link_to_follow->room_b;
	}
	else
	{
		*current_flow = B_TO_A;
		room_to_go = link_to_follow->room_a;
	}
	queue_add_item(&queue, room_to_go, previous);
}

void queue_add_item(t_queue **queue, t_room *next_room, \
		t_queueitem *previous)
{
	t_queueitem *new_item;

	new_item = (*queue)->arr + (*queue)->top;
	new_item->room = next_room;
	new_item->previous = previous;
	if (previous)
		new_item->steps = previous->steps + 1;
	bitmask_set_idx(&(*queue)->rooms_used, next_room->number);
	(*queue)->top++;
}

int	queue_can_be_opened(t_queue *queue, t_flowmap *stable_flowmap, t_room *start)
{
	const t_queueitem	startitem = {
		start,
		NULL,
		0
	};
	t_flowmap			*working_flowmap;
	t_link				*next_link;

	next_link = start->link_head;
	working_flowmap = get_working_flowmap();
	while (next_link)
	{
		if (next_link->room_a == start && queue_can_add_room(queue, \
					stable_flowmap, next_link->room_b, next_link))
			queue_add_item_and_update_flow(queue, working_flowmap, \
					next_link, (t_queueitem *)&startitem);
	}
	return (queue->top > 0);
}

void queue_clear(t_queue **queue)
{
	ft_bzero((void *)(*queue)->arr, sizeof(t_queueitem) * (*queue)->top);
	bitmask_clear(&(*queue)->rooms_used);
	(*queue)->top = 0;
}
