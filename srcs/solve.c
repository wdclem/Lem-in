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

static t_path *find_path(t_info *info, t_queueitem *start)
{
	t_queueitem *current_item;
	t_path		*new_path;
	int 		path_idx;
	static int	path_count;

	new_path = open_path(info, start->steps + 1);
	path_idx = start->steps;
	new_path->arr[path_idx--] = info->end;
	new_path->id = path_count++;
	current_item = start;
	while (path_idx >= 0)
	{
		add_room_to_path(&new_path, current_item->room, path_idx);
		current_item = current_item->previous;
		path_idx -= 1;
	}
	clear_dead_branch_from_queue(start);
	return (new_path);
}

static int	can_add_to_queue(t_queueitem *current_item, t_room *link_to)
{
	return (!check_bitmask_idx(&current_item->rooms_used, link_to->number));
}

static t_path	*bfs(t_queue *queue, t_info *info)
{
	t_queueitem *current_item;
	t_link		*current_link;
	static int	i;

	while (i >= 0)
	{
		current_item = &queue->arr[i];
		current_link = current_item->room->link_head;
		while (current_link != NULL)
		{
			if (current_link->link_to == info->end)
				return (find_path(info, current_item));
			if (can_add_to_queue(current_item, current_link->link_to))
				current_item->times_used += add_to_queue(&queue, current_link->link_to, \
						current_item);
			current_link = current_link->next;
		}
		if (!current_item->times_used)
			current_item->times_used = -1;
		i = next_available_index(queue, i, 1);
	}
	return (0);
}

int	solve(t_info *info)
{	
	static t_queue		queue;
	t_pathgroup	*groups;
	t_path		*next_path;

	groups = get_groups();
	printf("********SOLVE******\n");
	open_queue(&queue, info->start);
	printf("ants = %d\n", info->ants);
	while (info->total_paths < info->ants)
	{
		next_path = bfs(&queue, info);
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
