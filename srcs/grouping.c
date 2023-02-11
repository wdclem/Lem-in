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

static void	add_path_to_group(t_path *path, t_pathgroup *group)
{
	bitmask_set_idx(&path->groups, group->id);
	bitmask_add(&path->room_mask, &group->room_mask);
	group->arr[group->len] = path;
	group->total_path_len += path->len;
	group->len += 1;
	path->group_count += 1;
}

void	pathgroup_place_path(t_info *info, t_path *path, t_pathgroup *groups)
{
	int	group_idx;
	int	path_grouped;

	group_idx = 0;
	path_grouped = 0;
	while (group_idx < info->total_groups)
	{
		if (!bitmask_compare(&(groups + group_idx)->room_mask, &path->room_mask))
		{
			path_grouped = 1;
			add_path_to_group(path, (groups + group_idx));
		}
		group_idx++;
	}
	if (!path_grouped)
	{
		add_path_to_group(path, (groups + group_idx));
		(groups + group_idx)->id = group_idx;
		info->total_groups += 1;
	}
}
