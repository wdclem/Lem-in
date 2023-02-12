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

void	queue_open(t_queue *queue, t_room *start)
{
	t_link		*next_link;
	t_room		*next_room;
	t_flowmap	*flowmap;

	next_link = start->link_head;
	flowmap = get_working_flowmap();
	while (next_link)
	{
		next_room = next_link->room_a;
		flowmap->arr[next_link->number] = B_TO_A;
		if (next_room == start)
		{
			next_room = next_link->room_b;
			flowmap->arr[next_link->number] = A_TO_B;
		}
		queue_add_item(&queue, next_link, next_room);
		next_link = next_link->next;
	}
}

int	queue_add_item(t_queue **queue, t_link *previous_link, t_room *next_room)
{
	t_queueitem *new_item;

	new_item = (*queue)->arr + (*queue)->top;
	new_item->room = next_room;
	new_item->previous = previous_link;
	bitmask_set_idx(&(*queue)->rooms_used, next_room->number);
	(*queue)->top++;
	return (1);
}

void queue_clear(t_queue **queue)
{
	(*queue)->top = 0;
	ft_bzero((void *)(*queue)->arr, sizeof(t_queueitem) * MAX_QUEUE);
}
