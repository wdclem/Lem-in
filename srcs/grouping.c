/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
	/*   grouping.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccariou <ccariou@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 16:47:35 by ccariou           #+#    #+#             */
/*   Updated: 2023/02/09 12:03:25 by ccariou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	grouping_add_path_to_group(t_info *info, t_pathgroup *group, t_path *path)
{
	bitmask_clear_idx(&path->rooms_used, info->end->number);
	for (int i = 0; i < path->len; i++)
	{
		dprintf(2, "%s", path->room_arr[i]->id);
		if (i < path->len - 1)
			dprintf(2, " -> ");
	}
	dprintf(2, "\ntrying to add path id:%d len:%d to group:%dp:%p -- ", path->id, path->len, group->id, group);
//	if (bitmasks_share_bits(&group->rooms_used, &path->rooms_used))
//	{
//		dprintf(2, "can't because rooms overlap :((((\n");
//	}
//	else
//	{
		dprintf(2, "everything went better than expectation :)\n");
		bitmask_add(&path->rooms_used, &group->rooms_used);
		group->arr[group->len] = path;
		group->total_path_len += path->len;
		group->len++;
//	}
}
static t_path	*find_optimized_path(t_queue *queue, t_info *info, t_path *current_path)
{
	t_flowmap	*stable_flowmap;
	t_flowmap	*working_flowmap;
	t_queueitem	*current_item;
	t_link		*current_link;
	int			i;

	stable_flowmap = get_stable_flowmap();
	working_flowmap = get_working_flowmap();
	queue_clear(&queue);
	queue_add_item(&queue, info->end, NULL, NULL);
	i = 0;
	while (i < queue->top)
	{
		current_item = &queue->arr[i++];
		current_link = current_item->room->link_head;
		while (current_link != NULL)
		{
			if (current_link->link_to == info->start)
				return (path_make_next(info, current_item));
			if (bitmask_check_idx(&current_path->rooms_used, current_link->link_to->number) &&
					(stable_flowmap->arr[current_link->number] == OPEN || \
					working_flowmap->arr[current_link->number] == DOWNSTREAM))
			{
				queue_add_item(&queue, current_link->link_to,
						current_link, current_item);
			}
			current_link = current_link->next;
		}
	}
	return (NULL);
}

void	clear_path_from_stable_flowmap(t_info *info, t_path *path, t_flowmap *stable_flowmap)
{
	int	path_idx;

	path_idx = 0;
	while (path_idx < path->len - 1)
	{
		stable_flowmap->arr[path->link_arr[path_idx]->number + \
			(path->link_arr[path_idx]->number % 2 == 0) - (path->link_arr[path_idx]->number % 2 == 1)] = OPEN;
		stable_flowmap->arr[path->link_arr[path_idx]->number] = OPEN;
		path_idx++;
	}
	dprintf(2, "Clearpath: Stable path after clearing:\n");
	flowmap_debug_print(stable_flowmap, info->total_links);
}

void	grouping_optimize_pathgroup(t_queue *queue, t_info *info, t_pathgroup *group)
{
	t_path		*next_path;
	t_path		*new_path;

//	t_flowmap	stable_copy;
	int			path_idx;

	path_idx = 0;

	dprintf(2, "hello :)\n");
	while (path_idx < group->len)
	{
		next_path = group->arr[path_idx];
//		ft_memcpy((void *)&stable_copy, stable_flowmap, sizeof(t_flowmap));
		new_path = find_optimized_path(queue, info, next_path);
		if (new_path)
		{
			dprintf(2, "optimized path was:\n");
			for (int i = 0; i < new_path->len; i++)
			{
				dprintf(2, "%s", new_path->room_arr[i]->id);
				if (i < new_path->len - 1)
					dprintf(2, " -> ");
			}
			dprintf(2, "\n");
		}
		if (new_path && new_path->len < next_path->len)
		{

			dprintf(2, "AND IT WAS BETTER\n");

			group->arr[path_idx] = new_path;
			//flowmap_update_stable_map(&queue->arr[queue->top - 1], working_flowmap, stable_flowmap, info->total_links);
		}
//		else
//			ft_memcpy((void *)stable_flowmap, &stable_copy, sizeof(t_flowmap));
		path_idx++;
	}
}

