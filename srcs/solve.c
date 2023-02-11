/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccariou <ccariou@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 16:47:35 by ccariou           #+#    #+#             */
/*   Updated: 2023/02/07 12:22:25 by ccariou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static int	find_path_len(t_queue *queue, t_queueitem *start)
{
	t_queueitem	*seek;
	int len;

	seek = start;
	len = -1;
	while (seek->room != NULL)
	{
		len++;
		if (seek->previous == -1)
			break ;
		seek = &queue->arr[seek->previous];
	}
	return (len);
}

static t_path *find_path(t_info *info, t_queueitem *start)
{
	t_queueitem *current_item;
	t_path		*new_path;
	t_queue		*queue;
	int 		path_idx;
	static int	path_count;
	int			len;

	queue = get_queue();
	len = find_path_len(queue, start);
	new_path = open_path(info, len + 1);
	path_idx = len + 1;
	new_path->arr[path_idx--] = info->end;
	new_path->id = path_count++;
	current_item = start;
	while (path_idx >= 0)
	{
		add_room_to_path(&new_path, current_item->room, path_idx);
		current_item = &queue->arr[current_item->previous];
		path_idx -= 1;
	}
	clear_dead_branch_from_queue(start, queue);
	return (new_path);
}

static int	can_add_to_queue(t_queueitem *current_item, t_room *link_to)
{
	return (!check_bitmask_idx(&current_item->rooms_used, link_to->number));
}

static t_path *recurse(t_queue *queue, t_info *info)
{
	t_queueitem	*current_item;
	t_link		*current_link;
	int			cur_idx;
	
	while (queue->top > 0)
	{
		cur_idx = queue->top;
		while ((&queue->arr[cur_idx])->room == NULL)
			cur_idx--;
		if (cur_idx == -1)
			return (NULL);
		current_item = &queue->arr[queue->top - 1];
		current_link = current_item->room->link_head;
		while (current_link != NULL)
		{
			if (current_link->link_to == info->end)
			{
				queue->top--;
				return (find_path(info, current_item));
			}
			if (can_add_to_queue(current_item, current_link->link_to))
			{
				add_to_queue(&queue, current_link->link_to, current_item, queue->top - 1);
			}
		}
	}
	return (NULL);
}

t_path	*backtrack(t_queue *queue, t_info *info)
{
	(void) info;
	printf("Queue top when switching to backtrack:%d\n", queue->top);
	recurse(queue, info);
	return (NULL);
}

t_path	*bfs(t_queue *queue, t_info *info)
{
	t_queueitem *current_item;
	t_link		*current_link;
	static int	i;

	while (i >= 0 && (&queue->arr[i])->room != NULL)
	{
		current_item = &queue->arr[i];
		current_link = current_item->room->link_head;
		while (current_link != NULL)
		{
			if (current_link->link_to == info->end)
			{
				i = next_available_index_to_read(queue, i);
				if (i >= MAX_QUEUE)
				{
					printf("bfs: loop de loop1!\n");
					i = 0;
					i = next_available_index_to_read(queue, i);
				}
				return (find_path(info, current_item));
			}
			if (can_add_to_queue(current_item, current_link->link_to))
			{
				int ret = add_to_queue(&queue, current_link->link_to, current_item, i);
				if (ret <= 0)
					return 0;
				current_item->times_used += ret;
			}
			current_link = current_link->next;
		}
		if (!current_item->times_used)
			clear_dead_branch_from_queue(current_item, queue);
		i = next_available_index_to_read(queue, i);
		if (i >= MAX_QUEUE)
		{
			printf("bfs: loop de loop2!\n");
			i = 0;
			i = next_available_index_to_read(queue, i);
		}
		if (info->algo_changed)
			return (info->solve(queue, info));
	}
	return (0);
}

int	solve(t_info *info)
{	
	t_queue		*queue;
	t_pathgroup	*groups;
	t_path		*next_path;

	info->solve = &bfs;
	queue = get_queue();
	groups = get_groups();
	printf("********SOLVE******\n");
	open_queue(queue, info->start);
	printf("ants = %d\n", info->ants);
	while (info->total_paths < info->ants * 2)
	{
		next_path = info->solve(queue, info);
		if (!next_path)
		{
			printf("All paths found!\n");
			break ;
		}
		else
			find_groups_for_path(info, next_path, groups);
	}
	printf("teub a l'air, groups %d\n", info->total_groups);
	return (info->total_groups);
}
