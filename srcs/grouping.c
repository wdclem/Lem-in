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

void	grouping_add_path_to_group(t_pathgroup *group, t_path *path)
{
	for (int i = 0; i < path->len; i++)
	{
		dprintf(2, "%s", path->room_arr[i]->id);
		if (i < path->len - 1)
			dprintf(2, " -> ");
	}
	dprintf(2, "\ntrying to add path id:%d len:%d to group:%dp:%p -- ", path->id, path->len, group->id, group);
//	if (bitmask_compare(&group->rooms_used, &path->rooms_used))
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
static t_path	*find_optimized_path(t_queue *queue, t_info *info, t_flowmap *stable_flowmap, t_flowmap *working_flowmap)
{
	t_queueitem	*current_item;
	t_link		*current_link;
	int			i;

	ft_bzero((void *)&working_flowmap->arr, \
		sizeof(t_flowmask) * info->total_links);
	i = 0;
	queue_add_item(&queue, info->end, NULL, NULL);
	while (i < queue->top)
	{
		current_item = &queue->arr[i++];
		current_link = current_item->room->link_head;
		while (current_link != NULL)
		{
			if (stable_flowmap->arr[current_link->number] == OPEN)
			{
				queue_add_item_and_update_flow(queue, working_flowmap,
						current_link, current_item);
				if (current_link->link_to == info->start)
					return (path_make_next(info, &queue->arr[queue->top - 1]));
			}
			current_link = current_link->next;
		}
	}
	return (NULL);
}

void	clear_path_from_stable_flowmap(t_path *path, t_flowmap *stable_flowmap)
{
	int	path_idx;

	path_idx = 0;
	while (path_idx < path->len - 1)
	{
		stable_flowmap->arr[path->link_arr[path_idx]->number + \
			(path->link_arr[path_idx]->number % 2 == 0) - (path->link_arr[path_idx]->number % 2 == 1)] = OPEN;
		path_idx++;
	}
}

void	grouping_optimize_pathgroup(t_queue *queue, t_info *info, t_pathgroup *group)
{
	t_path		*next_path;
	t_path		*new_path;
	t_flowmap	*working_flowmap;
	t_flowmap	*stable_flowmap;
	t_flowmap	stable_copy;
	int			path_idx;

	path_idx = 0;
	working_flowmap = get_working_flowmap();
	stable_flowmap = get_stable_flowmap();
	while (path_idx < group->len)
	{
		next_path = group->arr[path_idx];
		ft_memcpy((void *)&stable_copy, stable_flowmap, sizeof(t_flowmap));
		clear_path_from_stable_flowmap(next_path, stable_flowmap);
		new_path = find_optimized_path(queue, info, stable_flowmap, working_flowmap);
		if (new_path && new_path->len < next_path->len)
		{

			dprintf(2, "optimized path was:\n");
			for (int i = 0; i < new_path->len; i++)
			{
				dprintf(2, "%s", new_path->room_arr[i]->id);
				if (i < new_path->len - 1)
					dprintf(2, " -> ");
			}
			group->arr[path_idx] = new_path;
			flowmap_update_stable_map(&queue->arr[queue->top - 1], working_flowmap, stable_flowmap, info->total_links);
		}
		else
			ft_memcpy((void *)stable_flowmap, &stable_copy, sizeof(t_flowmap));
		path_idx++;
	}
}

