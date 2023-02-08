/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_ants.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccariou <ccariou@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 09:43:23 by ccariou           #+#    #+#             */
/*   Updated: 2023/02/08 13:38:03 by ccariou          ###   ########.fr       */
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
//		printf("i == %d\n", i);
		if (path_idx == 0)
		{
			j = i;
			best_path = path_group->arr[path_idx];
		//	printf("path_group->first_room == %s, best_path->id == %d\n", path_group->arr[path_idx]->arr[0]->id, best_path->id);
//			printf("path_group->first_room == %s, best_path->id == %d\n", path_group->arr[path_idx]->arr[2]->id, best_path->id);
		}
		if (i < j)
		{
			j = i;
//			printf("path_idx == %d\n", path_idx);
			best_path = path_group->arr[path_idx];
//			printf("path_group->first_room == %s, best_path->id == %d\n", path_group->arr[path_idx]->arr[2]->id, best_path->id);
		//	printf("path_group->first_room == %s, best_path->id == %d\n", path_group->arr[path_idx]->arr[0]->id, best_path->id);
		}
		path_idx++;
	}
	//printf("best_path->id == %d\n", best_path->id);
	//printf("path_group->first_room == %s, best_path->id == %d\n", path_group->arr[path_idx]->arr[2]->id, best_path->id);
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
t_room *get_next_room(t_info *info, t_ant *ant)
{
	t_room	**copy;

	//printf("next room == %s\n", ant->path->arr[ant->path_idx + 1]->id);
	if (ant->path_idx == ant->path->len - 1)
		return (info->end);
	copy = &ant->path->arr[ant->path_idx];
	/*
	if ((*copy) == NULL)
	{
		printf("SAUCISSON\n");
		return (info->end);
	}
	*/
//	printf("arr-> 
	//if ((*copy)->occupied == 0)
//	printf("copy free == %d\n", (*copy)->free);
	if ((*copy)->occupied == 1)
		return(*copy);
	return (0);
}

int	move_ant(t_info *info, t_ant *ant)
{
	t_room	*next;

	next = get_next_room(info, ant);
//	if (next)
	//	printf("next == %s\n", next->id);
//	printf("CHORIZO\n");
//	printf("next == %s\n", next->id);
	if (next)
	{
		printf("L%d-%s", ant->id, next->id);
		ant->room->occupied = 1;
		ant->room = next;
		ant->room->occupied = 0;
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
//	int			path_idx;
	int			group_idx;
	double		turns;
	t_pathgroup *best_group;

	best = 0;
//	path_idx = 0;
	group_idx = 0;
	turns = 0;
	printf("in select group\n");
	printf("info->start == %s, info->end == %s\n", info->start->id, info->end->id);
	printf("group[%d] == %d\n", group_idx, group[group_idx]->id);
	while (group[group_idx]->total_path_len != 0)
	{
		//while (group[group_idx]->arr[path_idx]->len)
		//turns = ((group[group_idx]->arr[path_idx]->len + info->ants) / group[group_idx]->len);
		turns = ((group[group_idx]->total_path_len + info->ants) / group[group_idx]->len);
//		printf("group_path len == %d, ants == %d, turns == %f\n", group[group_idx]->total_path_len, info->ants, turns);
		if (turns - (int)turns != 0)
			turns += 1;
		if (group_idx == 0)
		{
			best = turns;
			best_group = group[group_idx];
		}
		if (turns < best)
		{
			best = turns;
			best_group = group[group_idx];
		}
		group_idx++;
	}
	printf("turns == %f, group[%d] == %d\n", turns, group_idx, group[group_idx]->id);
	printf("best group selected\n");
	return (best_group);
}

int move_ants2(t_info *info, t_pathgroup **path)
{
	int			ant_idx;
	int 		ants_arrived;
	t_pathgroup	*path_group;
	t_ant		**ants;

	info->ants = 100;
	ants = NULL;
	ants = (t_ant **)malloc(sizeof(t_ant *) * info->ants);
	ants = ants_array(info, ants);
	printf("group[0] == %d\n", path[0]->id);//arr[0]->arr[0]->id);
	printf("info->ant == %d\n", info->ants);
	path_group = select_group(info, path);
	ant_idx = 0;
	ants_arrived = 0;
//	info->ants = ANTCOUNT;
	while (ants_arrived < info->ants)
	{
		while (ant_idx < info->ants)
		{
//			printf("ca casse ici\n");
			if (ants[ant_idx]->room == info->start && ants[ant_idx]->path == NULL)
			{
				ants[ant_idx]->path = choose_path(path_group);
/*				int i = 0;
				while (ants[ant_idx]->path->arr[i])
				{
					printf("path == %s\n", ants[ant_idx]->path->arr[i]->id);
					i++;} */
//				ants[ant_idx]->path_idx = ants[ant_idx]->path->id;
//				printf("ants[ant_idx]->path_id = %d\n", ants[ant_idx]->path->id);
//				printf("Path selected\n");
/*				if(ants[2]->path)
					return (0);*/
			}
			//printf("ants[%d]->path == %d\n", ant_idx, ants[ant_idx]->path->id);
		//	printf("ant->room == %s\n", ants[ant_idx]->room->id);
		//	printf("info->end == %s\n", info->end->id);
		//	printf("info->start == %s\n", info->start->id);
			if (ants[ant_idx]->room == info->end)
			{
				ant_idx += 1;
				continue ;
			}
			ants_arrived += move_ant(info, &(*ants)[ant_idx]);
		//	printf("ant_idx == %d\n", ant_idx);
		//	printf("ant id == %d\n", ants[ant_idx]->id);
		// ants_arrived += move_ant(info, &(*ants)[ant_idx]);
		//	printf("ants_arrived == %d\n", ants_arrived);
//			if (ants[ant_idx].room == info->end)
//				ants_arrived += 1;
			ant_idx += 1;
			if (ant_idx < info->ants)
				printf(" ");
		}
		printf("\n");
		ant_idx = ants_arrived;
//		printf("ants_arrived == %d\n", ants_arrived);
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
