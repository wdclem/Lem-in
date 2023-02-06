/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_ants.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccariou <ccariou@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 09:43:23 by ccariou           #+#    #+#             */
/*   Updated: 2023/02/06 16:10:56 by ccariou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"
#define ANTCOUNT 20

/*
*/
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
		if (i > j)
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
//	int		count;
//	t_ant	*ants;

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

/* TODO save path set in info */
/*
t_array	*assign_ant(t_ant **array, t_path **path)
{
	int		i;

	i = 0;
	while (array)
	{
	}
	return (array);
}
*/
/*
int	move_ants(t_info *info, t_path **path)
{
	int	i;
//	int	j;
	t_ant	**ants;
//	char	*result;

	i = 0;
//	j = 0;
	while(path)
	{
		while (i < path[i]->len)
		{
//			printf("%s -> %s", path[i]->arr[j]->from->id, path[i]->arr[j]->link_to->id);
//			j += 1;
			if (i < path[i]->len)
				printf(", ");
			else
				printf("]\n");
		}
		i++;
	}
	ants = NULL;
	ants = (t_ant **)malloc(sizeof(t_ant *) * info->ants);
	ants = ants_array(info, ants);
	while(i < info->ants)
	{
		printf("array[i] == %d\n", ants[i]->id);
		i++;
	}
	return(0);
}
*/
t_room *get_next_room(t_ant *ant)
{
	t_room	**copy;

	copy = &ant->path->arr[ant->path_idx + 1];
	//if ((*copy)->occupied == 0)
//	printf("copy free == %d\n", (*copy)->free);
	if ((*copy)->occupied == 1)
		return(*copy);
	return (0);
}

int	move_ant(t_info *info, t_ant *ant)
{
	t_room	*next;

	next = get_next_room(ant);
//	if (next)
//		printf("next == %s\n", next->id);
	if (next)
	{
		printf("L%d-%s", ant->id, next->id);
		ant->room->occupied = 0;
		ant->room = next;
		ant->room->occupied = 1;
		ant->path_idx += 1;
	}
	if (next == info->end)
	{
		ant->room->occupied = 1;
		return (1);
	}
	return (0);
}

t_pathgroup	*select_group(t_info *info, t_pathgroup **group)
{
	int			best;
	int			path_idx;
	int			group_idx;
	double		turns;
	t_pathgroup *best_group;

	best = 0;
	path_idx = 0;
	group_idx = 0;
	turns = 0;
	printf("in select group\n");
	printf("group[%d] == %s\n", group_idx, group[group_idx]->arr[path_idx]->arr[path_idx]->id);
	while (group[group_idx])
	{
		turns = ((group[group_idx]->arr[path_idx]->len + info->ants) / group[group_idx]->len);
		if (turns - (int)turns != 0)
			turns += 1;
		if (group_idx == 0)
			best = turns;
		if (turns < best)
		{
			best = turns;
			best_group = group[group_idx];
		}
		group_idx++;
		printf("group_id ++\n");
	}
	printf("best group selected\n");
	return (best_group);
}

int move_ants2(t_info *info, t_pathgroup **path)
{
	int			ant_idx;
	int 		ants_arrived;
	t_pathgroup	*path_group;
	t_ant		**ants;

	ants = NULL;
	ants = (t_ant **)malloc(sizeof(t_ant *) * info->ants);
	ants = ants_array(info, ants);
	printf("group[0] == %d\n", path[0]->id);//arr[0]->arr[0]->id);
	path_group = select_group(info, path);
	ant_idx = 0;
	ants_arrived = 0;
	info->ants = ANTCOUNT;
	while (ants_arrived < info->ants)
	{
		while (ant_idx < info->ants)
		{
			if (ants[ant_idx]->room == info->start)
				ants[ant_idx]->path = choose_path(path_group);
			if (ants[ant_idx]->room == info->end)
			{
				ant_idx += 1;
				continue ;
			}
			ants_arrived += move_ant(info, &(*ants)[ant_idx]);
//			if (ants[ant_idx].room == info->end)
//				ants_arrived += 1;
			ant_idx += 1;
			if (ant_idx < info->ants)
				printf(" ");
		}
		printf("\n");
		ant_idx = ants_arrived;
	}
	return (1);
}

/*
void test_ant_move(void)
{
	t_path sample_path;
	t_ant *ants;
	char	*names[4] = {"first", "second", "third", "fourth"};
	t_info info = {
		0,
		0,
		ANTCOUNT,
		3,
		0,
		0,
		NULL,
		NULL,
		NULL,
	};
	
	sample_path.arr = (t_room **)calloc(4, sizeof(t_room *));
	for (int room_idx = 0; room_idx < 4; room_idx++)
	{
		sample_path.arr[room_idx] = (t_room *)calloc(1, sizeof(t_room));
		sample_path.arr[room_idx]->id = names[room_idx];
		sample_path.arr[room_idx]->occupied = 1;
	}
	sample_path.len = 4;
	info.start = sample_path.arr[0];
	info.end = sample_path.arr[3];
	ants = (t_ant *)calloc(ANTCOUNT, sizeof(t_ant));
	for (int ant_idx = 0; ant_idx < ANTCOUNT; ant_idx++)
	{
		ants[ant_idx].room = sample_path.arr[0];
		ants[ant_idx].path = &sample_path;
		ants[ant_idx].id = ant_idx;
		ants[ant_idx].path_idx = 0;
	}
	if (move_ants2(&info, ants))
		printf("Success :)\n");
}
*/
