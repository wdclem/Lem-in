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

void	open_queue(t_queue *queue, t_room *start)
{
	t_queueitem	*first_item;

	first_item = queue->arr;
	first_item->room = start;
	first_item->previous = NULL;
	first_item->steps = 0;
	queue->len = 1;
}

void	add_to_queue(t_queue **q, t_room *room, t_queueitem *previous)
{
	t_queueitem *new_item;

	new_item = (*q)->arr + (*q)->len;
	new_item->room = room;
	new_item->previous = previous;
	new_item->steps = previous->steps + 1;
	add_bitmask(&previous->rooms_used, &new_item->rooms_used);
	(*q)->len += 1;
	if ((*q)->len == MAX_QUEUE)
		printf("Queue overflow :(\n");
}
