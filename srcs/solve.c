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
	next_group = groups_arr + info->total_groups;
	next_group->id = info->total_groups++;
	queue_clear(&queue);
	queue_add_item(&queue, info->end, NULL, NULL);
	i = 0;
	while (i < queue->top)
	{
		next_path = flowmap_paths_remain(queue, stable_flowmap, info, &i);
		if (next_path)
			grouping_add_path_to_group(next_group, next_path);
	}
	t_flowmap *working_flowmap = get_working_flowmap();
	printf("Findpath: working flowmap at this point in time:\n");
	flowmap_debug_print(working_flowmap, info->total_links);
	printf("Stable flowmap at this point in time:\n");
	flowmap_debug_print(stable_flowmap, info->total_links);
	return (next_group);
}

static int	discover_flow_to_sink(t_queue *queue, t_flowmap *working_flowmap, \
		t_flowmap *stable_flowmap, t_info *info)
{
	t_queueitem *current_item;
	t_link		*current_link;
	t_room		*next_room;
	int			i;
	
	i = 1;
	while (i < queue->top)
	{
		current_item = &queue->arr[i++];
		current_link = current_item->room->link_head;
		while (current_link != NULL)
		{
			next_room = current_link->link_to;
			if (queue_can_add_room(queue, stable_flowmap, current_link))
			{
				queue_add_item_and_update_flow(queue, working_flowmap, \
					current_link, current_item);
				if (next_room == info->end)
					return (1);
			}
			current_link = current_link->next;
		}
	}
	return (0);
}

static int	can_find_next_pathgroup(t_queue *queue, t_info *info)
{
	t_pathgroup	*next_group;
	t_flowmap	*working_flowmap;
	t_flowmap	*stable_flowmap;

	working_flowmap = get_working_flowmap();
	stable_flowmap = get_stable_flowmap();
	if (!discover_flow_to_sink(queue, working_flowmap, stable_flowmap, info))
		return (0);
	flowmap_update_stable_map(&queue->arr[queue->top - 1], working_flowmap, \
			stable_flowmap, info->total_links);
	next_group = find_paths_for_next_group(queue, stable_flowmap, info);
	return (next_group->len > 0);
}

int	solve(t_info *info)
{	
	t_queue		*queue;
	t_flowmap	*stable_flowmap;

	queue = get_queue();
	stable_flowmap = get_stable_flowmap();
	while (queue_can_be_opened(queue, stable_flowmap, info))
	{
		if (!can_find_next_pathgroup(queue, info))
			break ;
	}
	return (info->total_groups);
}
