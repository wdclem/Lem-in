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

/* q should be a null pointer */
int	open_q(t_queue **q, int len)
{
	t_queue		*new_q;

	new_q = (t_queue *)ft_memalloc(sizeof(t_queue));
	if (!new_q)
		return (-1);
	reserve_q(&new_q, len);
	*q = new_q;
	return (1);
}

int	reserve_q(t_queue **q, int len)
{
	t_queueitem	*new_arr;
	int			new_size;

	if ((*q)->alloced >= len * (int)sizeof(t_queueitem))
		return (1);
	new_size = (*q)->alloced;
	while (new_size < len * (int)sizeof(t_queueitem))
		new_size *= 2;
	new_arr = (t_queueitem *)ft_memalloc(new_size);
	if (!new_arr)
		return (-1);
	ft_memcpy((void *)new_arr, (void *)(*q)->arr, (*q)->alloced);
	ft_memdel((void **)&(*q)->arr);
	(*q)->arr = new_arr;
	(*q)->alloced = new_size;
	(*q)->len = len;
	return (1);
}

int	add_to_q(t_queue **q, t_room *room, t_queueitem *previous)
{
	t_queueitem *new_item;

	if (reserve_q(q, (*q)->len + 1) < 0)
		return (-1);
	new_item = *(&(*q)->arr + (*q)->len + 1);
	new_item->room = room;
	new_item->previous = previous;
	new_item->steps = previous->steps + 1;
	(*q)->len += 1;
	return (1);
}

void	clear_q(t_queue **q)
{
	ft_bzero((*q)->arr, (*q)->len * sizeof(t_queueitem));
	(*q)->len = 0;
}

void	close_q(t_queue **q)
{
	ft_memdel((void **)&(*q)->arr);
	ft_memdel((void **)q);
}
