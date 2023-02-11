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

	next_link = start->link_head;
	while (next_link)
	{
		queue_add_item(&queue, next_link->link_to, NULL);
		next_link = next_link->next;
	}
}

int	queue_add_item(t_queue **queue, t_room *room, t_queueitem *previous)
{
	t_queueitem *new_item;

	new_item = (*queue)->arr + (*queue)->top;
	new_item->room = room;
	new_item->previous = previous;
	bitmask_set_idx(&(*queue)->rooms_used, room->number);
	if (previous)
		new_item->steps = previous->steps + 1;
	(*queue)->top++;
	return (1);
}

void queue_clear(t_queue **queue)
{
	(*queue)->top = 0;
	ft_bzero((void *)(*queue)->arr, sizeof(t_queueitem) * MAX_QUEUE);
}
