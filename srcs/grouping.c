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

static inline void set_bitmask_idx(t_bitmask *mask, int idx)
{
	*(long *)mask[idx / sizeof(long)] |= 1 << (long)idx % sizeof(long);
}



static void add_bitmask(t_bitmask *src, t_bitmask *dst)
{
	int		long_idx;

	long_idx = 0;
	while (long_idx < (int)MASKSIZE)
	{
		*(long *)dst[long_idx / sizeof(long)] |= \
				*(long *)src[long_idx / sizeof(long)];
		long_idx++;
	}
}

static void	add_path_to_group(t_path *path, t_pathgroup *group)
{
	set_bitmask_idx(&path->groups, group->id);
	add_bitmask(&path->rooms_used, &group->rooms_used);
	group->capacity += path->len;
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
	new_group->arr[new_group->len] = path;
	new_group->len++;
	add_path_to_group(path, new_group);
	return (new_group);
}

static int maskcmp(t_bitmask *left, t_bitmask *right)
{
	int		long_idx;

	long_idx = 0;
	while (long_idx < (int)MASKSIZE)
	{
		if ((long)left[long_idx] & (long)right[long_idx])
			return (1);
		long_idx++;
	}
	return (0);
}

void find_groups_for_path(t_path *path, t_pathgroup **groups)
{
	int	group_idx;

	group_idx = 0;
	while (groups[group_idx] != NULL)
	{
		if (!maskcmp(&groups[group_idx]->rooms_used, &path->rooms_used))
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
