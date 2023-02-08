/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_ants.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccariou <ccariou@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 09:43:23 by ccariou           #+#    #+#             */
/*   Updated: 2023/02/09 14:15:52 by ccariou          ###   ########.fr       */
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

t_ant	*init_ant(t_info *info, int *id)
{
	t_ant *ant;

	ant = (t_ant *)malloc(sizeof(t_ant));
	ant->room = info->start;
	ant->id = (*id)++;
	return(ant);
}

t_ant	**ants_array(t_info *info, t_ant **array)
{
	int		i;
	int		id;

	i = 0;
	id = 1;
	printf("info->ants == %d\n", info->ants);
	while (i < info->ants)
	{
		array[i] = init_ant(info, &id);
		i++;
	}
	printf("array created\n");
	return(array);
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
		printf("L%d-%s", ant->id, next->id);
		ant->room->occupied = 0;
		ant->room = next;
		ant->room->occupied = 1;
		ant->path_idx += 1;
		printf(" ");
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
	printf("in select group\n");
	printf("info->start == %s, info->end == %s\n", info->start->id, info->end->id);
	printf("group[%d] == %d\n", group_idx, (groups + group_idx)->id);
	while (group_idx < info->total_groups)
	{
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
	printf("turns == %f, group[%d] == %d\n", turns, group_idx, (groups + group_idx)->id);
	printf("best group selected, was %d\n", best_group->id);
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
	path_group = select_group(info, get_groups());
	ant_idx = 0;
	ants_arrived = 0;
	while (ant_idx < info->ants)
	{
		ants[ant_idx]->path = choose_path(path_group);
		printf("Path selected for ant %d: was %d\n", ants[ant_idx]->id, ants[ant_idx]->path->id);
		ant_idx++;
	}
	while (ants_arrived < info->ants)
	{
		ant_idx = ants_arrived;
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
		printf("\n");
	}
	return (1);
}
