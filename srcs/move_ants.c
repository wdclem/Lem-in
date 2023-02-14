/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_ants.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccariou <ccariou@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 09:43:23 by ccariou           #+#    #+#             */
/*   Updated: 2023/02/07 12:59:31 by ccariou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

t_path	*choose_path(t_pathgroup *path_group)
{
	t_path	*best_path;
	int		path_idx;
	int		i;
	int		j;

	path_idx = 0;
	i = 0;
	j = 0;
	while (path_group->arr[path_idx])
	{
		i = path_group->arr[path_idx]->len + path_group->arr[path_idx]->ants_in;
		if (path_idx == 0)
		{
			j = i;
			best_path = path_group->arr[path_idx];
		}
		if (i < j)
		{
			j = i;
			best_path = path_group->arr[path_idx];
		}
		path_idx++;
	}
	best_path->ants_in += 1;
	return (best_path);
}

t_room *get_next_room(t_ant *ant)
{
	t_room	*copy;

	copy = ant->path->arr[ant->path_idx];
	if (copy->occupied == 0)
		return (copy);
	return (0);
}

int	move_ant(t_info *info, t_ant *ant)
{
	t_room	*next;

	next = get_next_room(ant);
	if (next)
	{
		dprintf(2, "L%d-%s", ant->id, next->id);
		ant->room->occupied = 0;
		ant->room = next;
		ant->room->occupied = 1;
		ant->path_idx += 1;
		dprintf(2, " ");
	}
	if (next == info->end)
	{
		ant->room->occupied = 0;
		return (1);
	}
	return (0);
}

t_pathgroup	*select_group(t_info *info, t_pathgroup *groups)
{
	int			best;
	int			group_idx;
	double		turns;
	t_pathgroup	*best_group;

	best = 0;
	group_idx = 0;
	turns = 0;
	dprintf(2, "in select group\n");
	dprintf(2, "info->start == %s, info->end == %s\n", info->start->id, info->end->id);
	dprintf(2, "group[%d] == %d\n", group_idx, (groups + group_idx)->id);
	while (group_idx < info->total_groups)
	{
		printf("Some group stats:\ngroup id: %d\ngroup len: %d\ngroup total_path_len: %d\n", 
				(groups + group_idx)->id, (groups + group_idx)->len, (groups + group_idx)->total_path_len);
		turns = (((groups + group_idx)->total_path_len + info->ants)
				/ (groups + group_idx)->len);
		if (turns - (int)turns != 0)
			turns += 1;
		if (group_idx == 0)
		{
			best = turns;
			best_group = groups + group_idx;
		}
		if (turns < best)
		{
			best = turns;
			best_group = groups + group_idx;
		}
		group_idx++;
	}
	dprintf(2, "turns == %f, group[%d] == %d\n", turns, group_idx, (groups + group_idx)->id);
	dprintf(2, "best group selected, was %d\n", best_group->id);
	return (best_group);
}

int	move_ants2(t_info *info)
{
	int			ant_idx;
	int			ants_arrived;
	t_pathgroup	*path_group;
	t_ant		**ants;

	ants = NULL;
	ants = (t_ant **)malloc(sizeof(t_ant *) * info->ants);
	ants = ants_array(info, ants);
	path_group = select_group(info, get_groups_arr());
	ant_idx = 0;
	ants_arrived = 0;
	while (ant_idx < info->ants)
	{
		ants[ant_idx]->path = choose_path(path_group);
		dprintf(2, "Path selected for ant %d: was %d\n", ants[ant_idx]->id, ants[ant_idx]->path->id);
		ant_idx++;
	}
	while (ants_arrived < info->ants)
	{
		ant_idx = 0;
		while (ant_idx < info->ants)
		{
			if (ants[ant_idx]->room == info->end)
			{
				ant_idx += 1;
				continue ;
			}
			ants_arrived += move_ant(info, ants[ant_idx]);
			ant_idx += 1;
		}
		dprintf(2, "\n");
	}
	return (1);
}
