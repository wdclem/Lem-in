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
		dprintf(2, "%s", path->arr[i]->id);
		if (i < path->len - 1)
			dprintf(2, " -> ");
	}
	dprintf(2, "\ntrying to add path id:%d len:%d to group:%dp:%p -- ", path->id, path->len, group->id, group);
	if (bitmask_compare(&group->rooms_used, &path->rooms_used))
	{
		dprintf(2, "can't because rooms overlap :((((\n");
	}
	else
	{
		dprintf(2, "everything went better than expectation :)\n");
		bitmask_add(&path->rooms_used, &group->rooms_used);
		group->arr[group->len] = path;
		group->total_path_len += path->len;
		group->len++;
	}
}
/*
void	grouping_optimize_pathgroup(t_queue *queue, t_info *info, t_pathgroup *group)
{
	t_path		*next_path;
	t_path		*new_path;
	t_flowmap	*working_flowmap;
	t_flowmap	*stable_flowmap;
	int			path_idx;

	path_idx = 0;
	working_flowmap = get_working_flowmap();
	stable_flowmap = get_stable_flowmap();
	while (path_idx < group->len)
	{
		next_path = group->arr[path_idx];
		remove_path_from_stable_flowmap(next_path, stable_flowmap, working_flowmap);
		new_path = find_optimized_path(queue, info->end, stable_flowmap, working_flowmap);
		if (new_path->len < next_path->len)
		{
			ft_memcpy(&group->arr[path_idx], new_path, sizeof(t_path));
			flowmap_update_stable_map(i
		}
	}
}
*/
