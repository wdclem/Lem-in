/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccariou <ccariou@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 16:47:35 by ccariou           #+#    #+#             */
/*   Updated: 2023/02/03 17:51:14 by ccariou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static void	add_path_to_group(t_path *path, t_pathgroup *group)
{
	set_bitmask_idx(&path->groups, group->id);
	add_bitmask(&path->room_mask, &group->room_mask);
	group->arr[group->len] = path;
	group->total_path_len += path->len;
	group->len += 1;
	path->group_count += 1;
}

t_pathgroup *new_group(t_path *path)
{
	t_pathgroup	*new_group;
	t_path		**new_arr;

	new_group = (t_pathgroup *)ft_memalloc(sizeof(t_pathgroup));
	new_arr = (t_path **)ft_memalloc(sizeof(t_path) * MAX_PATH);
	if (!(new_group && new_arr))
		return (NULL);
	new_group->arr = new_arr;
	add_path_to_group(path, new_group);
	return (new_group);
}


void find_groups_for_path(t_path *path, t_pathgroup **groups)
{
	int	group_idx;

	group_idx = 0;
	while (groups[group_idx] != NULL)
	{
		if (!maskcmp(&groups[group_idx]->room_mask, &path->room_mask))
		{
			add_path_to_group(path, groups[group_idx]);
		}
		group_idx++;
	}
	if (path->group_count == 0)
	{
		groups[group_idx] = new_group(path);
	}
}
