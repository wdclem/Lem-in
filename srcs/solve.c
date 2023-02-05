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
const unsigned int page_size = PAGE_SIZE;

static t_path *find_path(t_queueitem *start)
{
	t_queueitem *current_item;
	t_path		*new_path;
	int 		path_idx;
	static int	path_count;

	new_path = open_path(start->steps);
	if (!new_path)
		return (NULL);
	path_idx = start->steps - 1;
	current_item = start;
	while (path_idx >= 0)
	{
		add_room_to_path(&new_path, current_item->room, path_idx);
		current_item = current_item->previous;
		path_idx -= 1;
	}
	new_path->id = path_count++;
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
					return (find_path(current_item));
			}
			current_link = current_link->next;
		}
	}
	return (0);
}


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
			find_groups_for_path(next_path, groups);
			paths[info->total_paths] = next_path;
			info->total_paths += 1;
		}
		printf("********path#%d len:%d******\n", next_path->id, next_path->len);
		printf("uses following rooms:\n");
		print_bitmask(&next_path->room_mask);
		int i = 0;
		while (i < next_path->len)
		{
			printf("%s", next_path->arr[i]->id);
			if (i < next_path->len - 1)
				printf("->");
			i++;
		}
		printf("\n");
		round++;
	}
	int group_idx = 0;
	while (groups[group_idx] != NULL)
	{
		t_pathgroup *current_group = groups[group_idx];
		printf("********group#%d, len = %d******\n", current_group->id, current_group->len);
		printf("contains following paths: ");
		for (int i = 0; i < current_group->len; i++)
		{
			printf("(%d)", current_group->arr[i]->id);
			if (i < current_group->len - 1)
				printf(" ");
		}
		printf("\n");
		printf("uses following rooms:\n");
		print_bitmask(&current_group->room_mask);
		printf("\n");
		group_idx++;
	}
	printf("teub a l'air\n");
//	test_ant_move();
//	move_ants(info, paths);
//	send_ants(info, path);
//	printf("path link_to == %s\n", path->link_to->id);
//	free(queue);
	return (1);
}
