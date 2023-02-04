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

static void add_room_to_path(t_path **path, t_room *room, int index)
{
	t_room	**ptr;

	if (index > (*path)->len)
		return ;
	ptr = (*path)->arr + index;
	*ptr = room;
}

static t_path *find_path(t_queueitem *start, t_info *info)
{
	t_queueitem *current_item;
	t_path		*new_path;
	int 		i;

	new_path = open_path(start->steps + 2);
	i = start->steps + 1;
	if (!new_path)
		return (NULL);
	add_room_to_path(&new_path, info->end, i--);
	current_item = start;
	while (i > 0)
	{
		add_room_to_path(&new_path, current_item->room, i);
		current_item = current_item->previous;
		i -= 1;
	}
	add_room_to_path(&new_path, info->start, i);
	return (new_path);
}

static int	can_add_to_queue(t_queueitem *current_item, t_room *link_to)
{
	t_queueitem	*seek;

	seek = current_item;
	while (seek)
	{
		if (seek->room == link_to)
			return (0);
		seek = seek->previous;
	}
	return (1);
}

static t_path	*bfs(t_queue *queue, t_info *info)
{
	t_queueitem *current_item;
	t_room		*current_room;
	t_link		*current_link;
	static int	i;

	while (i < queue->len)
	{
		current_item = &queue->arr[i++];
		current_room = current_item->room;
		current_link = current_room->link_head;
		while (current_link != NULL)
		{
			if (can_add_to_queue(current_item, current_link->link_to))
			{
				//TODO should there be more conditions to stop searching?
				//currently we potentially iterate through every node in
				//graph multiple times
				if (!add_to_queue(&queue, current_link->link_to, current_item))
					return (0);
				if (current_link->link_to == info->end)
					return (find_path(current_item, info));
			}
			current_link = current_link->next;
		}
	}
	return (0);
}

t_pathgroup *new_group(t_path *path)
{
	t_pathgroup	*new;

	new = (t_pathgroup *)ft_memalloc(sizeof(t_pathgroup));
	new->arr[new->len] = path;
//	ft_dintarr_copy(&path->rooms_used, &new->rooms_used, path->len);
	new->len++;
	return (new);
}

static int path_rooms_overlap(t_dintarr *left, t_dintarr *right)
{
	(void) left;
	(void) right;
	return (0);
}

static void place_path_in_group(t_path *path, t_pathgroup **groups)
{
	int	group_idx;

	group_idx = 0;
	while (groups[group_idx] != NULL)
	{
		if (!path_rooms_overlap(groups[group_idx]->rooms_used, path->rooms_used))
		{
			ft_dintarr_add(&path->groups, group_idx);
		}
	}
	if (path->groups->len == 0)
	{
		groups[group_idx] = new_group(path);
	}
}

#define MAX_PATH 1024
#define MAX_GROUPS 256

int	solve(t_info *info)
{	
	t_queue		*queue;
	t_path		**paths;
	t_pathgroup **groups;
	t_path		*next_path;
	int			round;

	round = 1;
	//#TODO should path container be dynamic?
	paths = (t_path **)ft_memalloc(MAX_PATH * sizeof(t_path *));
	groups = (t_pathgroup **)ft_memalloc(sizeof(t_pathgroup *) * \
			MAX_GROUPS);
	printf("********SOLVE******\n");
	queue = open_queue(info->start, 80);
	if (!queue)
		return (ERROR);
	printf("ants = %d\n", info->ants);
	while (info->total_paths < info->ants)
	{
		printf("\nROUND %d, total_paths = %d\n", round, info->total_paths);
		next_path = bfs(queue, info);
		if (!next_path)
		{
			printf("All paths found!\n");
			close_queue(&queue);
			break ;
		}
		else
		{
			place_path_in_group(next_path, groups);
			paths[info->total_paths] = next_path;
			info->total_paths += 1;
		}
		printf("********path, len = %d******\n[", next_path->len);
		int i = 0;
		while (i < next_path->len)

		{
			printf("%s", next_path->arr[i]->id);
			if (i < next_path->len - 1)
				printf("->");
		}
		printf("\n");
		round++;
	}
	printf("teub a l'air\n");
//	test_ant_move();
//	move_ants(info, paths);
//	send_ants(info, path);
//	printf("path link_to == %s\n", path->link_to->id);
//	free(queue);
	return (1);
}
