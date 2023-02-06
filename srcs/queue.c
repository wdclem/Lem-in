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

int	add_to_queue(t_queue **q, t_room *room, t_queueitem *previous)
{
	t_queueitem *new_item;

	new_item = (*q)->arr + (*q)->len;
	new_item->room = room;
	new_item->previous = previous;
	new_item->steps = previous->steps + 1;
	(*q)->len += 1;
	//printf("linking from %s to %s\n", previous->room->id, room->id);
	//printf("%zu -> %d\n", previous - (*q)->arr, (*q)->len-1);
	return (1);
}

void	clear_queue(t_queue **q)
{
	ft_bzero((*q)->arr + 1, (*q)->len * sizeof(t_queueitem) - 1);
	(*q)->len = 1;
}
