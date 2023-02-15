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

t_pathgroup	*find_paths_for_next_group(t_queue *queue, \
		t_flowmap *stable_flowmap, t_info *info)
{
	t_pathgroup	*groups_arr;
	t_pathgroup	*next_group;
	t_path		*next_path;
	int			i;

	groups_arr = get_groups_arr();
	next_group = &groups_arr[info->total_groups];
	next_group->id = info->total_groups;
	queue_clear(&queue);
	queue_add_item(&queue, info->end, NULL, NULL);
	i = 0;
	while (i < queue->top)
	{
		next_path = flowmap_paths_remain(queue, stable_flowmap, info, &i);
		if (next_path)
			grouping_add_path_to_group(info, next_group, next_path);
	}
	return (next_group);
}

static int	discover_flow_to_sink(t_queue *queue, t_flowmap *stable_flowmap, \
		t_info *info, int *i)
{
	t_flowmap	*working_flowmap;
	t_queueitem	*current_item;
	t_link		*current_link;

	working_flowmap = get_working_flowmap();
	while (*i < queue->top)
	{
		current_item = &queue->arr[(*i)++];
		if (!current_item->was_forced_to_move && \
				flowmap_forces_movement(queue, info, current_item))
			continue ;
		current_link = current_item->room->link_head;
		while (current_link != NULL)
		{
			if (queue_can_add_room(queue, stable_flowmap, current_link, OPEN))
			{
				queue_add_item_and_update_flow(queue, working_flowmap, \
					current_link, current_item);
				if (current_link->link_to == info->end)
					return (1);
			}
			current_link = current_link->next;
		}
	}
	return (0);
}

static t_pathgroup	*get_next_pathgroup(t_queue *queue, t_info *info)
{
	t_pathgroup	*next_group;
	t_flowmap	*working_flowmap;
	t_flowmap	*stable_flowmap;
	int			i;

	working_flowmap = get_working_flowmap();
	stable_flowmap = get_stable_flowmap();
	i = 0;
	if (discover_flow_to_sink(queue, stable_flowmap, info, &i))
		flowmap_update_stable_map(&queue->arr[queue->top - 1], \
				working_flowmap, stable_flowmap);
	next_group = find_paths_for_next_group(queue, stable_flowmap, info);
	bitmask_clear(&queue->path_rooms_used);
	return (next_group);
}

int	solve(t_info *info)
{	
	t_queue		*queue;
	t_flowmap	*stable_flowmap;
	t_pathgroup	*next_group;
	t_pathgroup	*previous_group;
	int			best_score;

	queue = get_queue();
	stable_flowmap = get_stable_flowmap();
	best_score = MAX_ROOMS;
	previous_group = NULL;
	while (queue_can_be_opened(queue, stable_flowmap, info))
	{
		next_group = get_next_pathgroup(queue, info);
		next_group->score = grouping_score_group(info, next_group);
		if (next_group->score > best_score || (previous_group && \
				bitmasks_are_equal(&previous_group->rooms_used, \
				&next_group->rooms_used)))
			break ;
		best_score = next_group->score;
		previous_group = next_group;
		info->total_groups++;
	}
	return (info->total_groups);
}
