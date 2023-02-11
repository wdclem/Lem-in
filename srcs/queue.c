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

void	open_queue(t_queue *queue, t_room *start)
{
	t_link		*next_link;

	next_link = start->link_head;
	while (next_link)
	{
		add_to_queue(&queue, next_link->link_to, NULL, queue->top);
		next_link = next_link->next;
	}
}

void	clear_dead_branch_from_queue(t_queueitem *dead_end, t_queue *queue)
{
	int previous;

	previous = dead_end->previous;
	ft_bzero((void *)dead_end, sizeof(t_queueitem));
	if (previous > 0)
	{
		(&queue->arr[dead_end->previous])->times_used--;
		if ((&queue->arr[dead_end->previous])->times_used == 0)
			clear_dead_branch_from_queue(&queue->arr[dead_end->previous],
					queue);
	}
}

int	add_to_queue(t_queue **queue, t_room *room, t_queueitem *previous, int index)
{
	t_queueitem *new_item;
	int			next_idx;

	next_idx = next_available_index_to_write(*queue, (*queue)->top);
	if (next_idx == -1)
		return (0);
	new_item = (*queue)->arr + next_idx;
	new_item->room = room;
	new_item->previous = index;
	set_bitmask_idx(&new_item->rooms_used, room->number);
	if (previous)
	{
		add_bitmask(&previous->rooms_used, &new_item->rooms_used);
	}
	else
	{
		new_item->previous = -1;
	}
	(*queue)->top = next_idx; 
	return (1);
}

void	garbage_collect(t_queue *queue)
{
	int	queue_idx;
	int	noms = 0;
	int fulls = 0;

	queue_idx = MAX_QUEUE - 1;
	printf("GARBAGE DAY!\n");
	while (queue_idx >= 0)
	{
		if ((queue->arr + queue_idx)->times_used == -1)
		{
			noms++;
			clear_dead_branch_from_queue(&queue->arr[queue_idx], queue);
		}
		else
		{
			fulls++;
		}
		queue_idx--;
	}
	printf("%d noms were made, %d fulls were left\n", noms, fulls);
}

void	change_solve_algorithm(t_path *(*solve)(struct s_queue *,
				struct s_info *))
{
	t_info	*info;

	info = get_info();
	info->solve = solve;
	info->algo_changed = 1;
}

int		next_available_index_to_write(t_queue *queue, int cur_idx)
{
	int			next_idx;

	next_idx = cur_idx;
	while ((&queue->arr[next_idx])->room != NULL)
	{
		next_idx++;
		if (next_idx == MAX_QUEUE / 2)
		{
			printf("Queue half full!\n");
			change_solve_algorithm(backtrack);
		}
		if (next_idx >= MAX_QUEUE)
		{
			garbage_collect(queue);
			printf("write: loop de loop!\n");
			next_idx = 0;
		}
		if (next_idx == cur_idx)
			return (-1);
	}
	return (next_idx);
}

int		next_available_index_to_read(t_queue *queue, int cur_idx)
{
	int			next_idx;

	next_idx = cur_idx + 1;
	if (next_idx >= MAX_QUEUE)
	{
		printf("read: loop de loop1!\n");
		next_idx = 0;
	}
	while ((&queue->arr[next_idx])->room == NULL && \
			(&queue->arr[next_idx])->times_used == 0)
	{
		if (next_idx >= MAX_QUEUE)
		{
			printf("read: loop de loop2!\n");
			next_idx = 0;
		}
		else
			next_idx++;
		if (next_idx == cur_idx)
			return (-1);
	}
	return (next_idx);
}
