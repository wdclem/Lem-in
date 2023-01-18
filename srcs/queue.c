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

t_queue	*open_queue(t_room *start, int size)
{
	t_queue		*new_q;
	t_queueitem	*first_item;

	new_q = (t_queue *)ft_memalloc(sizeof(t_queue));
	if (!new_q)
		return (NULL);
	new_q->alloced = 2;
	if (!reserve_space_in_queue(&new_q, size))
		close_queue(&new_q);
	first_item = new_q->arr;
	first_item->room = start;
	first_item->previous = NULL;
	first_item->steps = 0;
	new_q->len = 1;
	return (new_q);
}

int	reserve_space_in_queue(t_queue **q, int size)
{
	t_queueitem	*new_arr;
	int			new_alloc;

	if ((*q)->alloced >= size * (int)sizeof(t_queueitem))
		return ((*q)->alloced / (int)sizeof(t_queueitem));
	new_alloc = (*q)->alloced;
	while (new_alloc < size * (int)sizeof(t_queueitem))
		new_alloc *= 2;
	new_arr = (t_queueitem *)ft_memalloc(new_alloc);
	if (!new_arr)
		return (0);
	ft_memcpy((void *)new_arr, (void *)(*q)->arr, \
			(*q)->len * sizeof(t_queueitem));
	ft_memdel((void **)&(*q)->arr);
	(*q)->arr = new_arr;
	(*q)->alloced = new_alloc;
	return ((*q)->alloced / (int)sizeof(t_queueitem));
}

int	add_to_queue(t_queue **q, t_room *room, t_queueitem *previous)
{
	t_queueitem *new_item;

	if (reserve_space_in_queue(q, (*q)->len + 1) < 0)
		return (0);
	new_item = (*q)->arr + (*q)->len;
	new_item->room = room;
	new_item->previous = previous;
	new_item->steps = previous->steps + 1;
	(*q)->len += 1;
	return (1);
}

void	clear_queue(t_queue **q)
{
	ft_bzero((*q)->arr + 1, (*q)->len * sizeof(t_queueitem) - 1);
	(*q)->len = 1;
}

void	close_queue(t_queue **q)
{
	ft_memdel((void **)&(*q)->arr);
	ft_memdel((void **)q);
}
