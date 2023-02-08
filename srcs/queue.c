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
	queue->usage++;
	add_to_queue(&queue, start->link_head->link_to, first_item);
}

void	clear_dead_branch_from_queue(t_queue **queue, t_queueitem *dead_end)
{
	t_queueitem *current;

	current = dead_end;
	printf("clearing branch, rooms & times_used: ");
	while(current->steps > 1)
	{
		printf("(%s:%d) ", current->room->id, current->times_used);
		current->times_used--;
		(*queue)->usage--;
		current = current->previous;
	}
}

int	add_to_queue(t_queue **queue, t_room *room, t_queueitem *previous)
{
	t_queueitem *new_item;
	int			next_idx;

	next_idx = (*queue)->top + 1;
	while(((*queue)->arr + next_idx)->room)
	{
		next_idx++;
		if (next_idx == MAX_QUEUE)
		{
			printf("loop de loop!\n");
			next_idx = 0;
		}
	}
	new_item = (*queue)->arr + next_idx;
	new_item->room = room;
	new_item->previous = previous;
	new_item->steps = previous->steps + 1;
	set_bitmask_idx(&new_item->rooms_used, room->number);
	add_bitmask(&previous->rooms_used, &new_item->rooms_used);
	(*queue)->top = next_idx; 
	(*queue)->usage += 1;
	return (1);
}
