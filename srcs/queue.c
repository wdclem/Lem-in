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
#include "libft.h"

int	queue_add_item_and_update_flow(t_queue *queue, t_flowmap *flowmap,
		t_link *link_to_follow, t_room *room_to_go)
{
	t_flowmask	*current_flow;

	current_flow = &flowmap->arr[link_to_follow->number];
	if (room_to_go == link_to_follow->room_a)
		*current_flow = A_TO_B;
	else
		*current_flow = B_TO_A;
	bitmask_set_idx(&queue->rooms_used, room_to_go->number);
	queue_add_item(&queue, link_to_follow, room_to_go);
	return (0);
}

int	queue_can_add_item(t_queue *queue, t_flowmap *flowmap, t_room *source, t_link *link_to_follow)
{
	int	ret;

	ret = bitmask_check_idx(&queue->rooms_used, source->number);
	ret &= flowmap->arr[link_to_follow->number] != BLOCKED;
	return (ret);
}

int	queue_can_be_opened(t_queue *queue, t_flowmap *flowmap, t_room *start)
{
	t_link		*next_link;
	t_room		*next_room;
	t_flowmask	*next_flow;

	next_link = start->link_head;
	while (next_link)
	{
		next_flow = &flowmap->arr[next_link->number];
		if (*next_flow == BLOCKED)
			continue;
		if (start == next_link->room_a && *next_flow == B_TO_A)
			continue;
		if (*next_flow == A_TO_B
		if (next_room == next_link->room_a && *next_flow == B_TO_A)
			continue ;
		if (next_room == next_link->room_b && *next_flow == B_TO_A)
			continue;
	}
	return (queue->top > 0);
}

int	queue_add_item(t_queue **queue, t_link *previous_link, t_room *next_room)
{
	t_queueitem *new_item;

	new_item = (*queue)->arr + (*queue)->top;
	new_item->room = next_room;
	new_item->previous = previous_link;
	(*queue)->top++;
	return (1);
}

void queue_clear(t_queue **queue)
{
	ft_bzero((void *)(*queue)->arr, sizeof(t_queueitem) * (*queue)->top);
	(*queue)->top = 0;
}
