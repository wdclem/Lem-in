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

void	free_ants(t_ant	**ant_arr, int total_ants)
{
	int	ant_idx;

	ant_idx = 0;
	while (ant_idx < total_ants)
	{
		ft_memdel((void **)&ant_arr[ant_idx]);
		ant_idx++;
	}
	free(ant_arr);
}

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

int	move_ant(t_info *info, t_ant *ant)
{
	t_room	*next;

	next = ant->path->room_arr[ant->path_idx];
	if (next->occupied == 0)
	{
		ft_printf("L%d-%s", ant->id, next->id);
		ant->room->occupied = 0;
		ant->room = next;
		ant->room->occupied = 1;
		ant->path_idx += 1;
		ft_printf(" ");
		if (next == info->end)
		{
			ant->room->occupied = 0;
			return (1);
		}
	}
	return (0);
}

static void	step_ants(t_info *info, t_ant **ants, int *ants_arrived, int *lines)
{
	int	ant_idx;

	ant_idx = 0;
	while (ant_idx < info->ants)
	{
		if (ants[ant_idx]->room == info->end)
		{
			ant_idx += 1;
			continue ;
		}
		*ants_arrived += move_ant(info, ants[ant_idx]);
		ant_idx += 1;
	}
	(*lines)++;
	ft_printf("\n");
}

int	move_ants(t_info *info, t_pathgroup *best_group)
{
	int			ant_idx;
	int			ants_arrived;
	t_ant		**ants;
	int			lines;

	ants = (t_ant **)ft_memalloc(sizeof(t_ant *) * info->ants);
	ants = ants_array(info, ants);
	grouping_optimize_pathgroup(get_queue(), info, best_group);
	ant_idx = 0;
	ants_arrived = 0;
	while (ant_idx < info->ants)
	{
		ants[ant_idx]->path = choose_path(best_group);
		ant_idx++;
	}
	lines = 0;
	while (ants_arrived < info->ants)
	{
		step_ants(info, ants, &ants_arrived, &lines);
	}
	free_ants(ants, info->ants);
	ft_printf("line count was %d\n", lines);
	return (1);
}
