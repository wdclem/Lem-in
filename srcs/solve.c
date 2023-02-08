/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccariou <ccariou@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 16:47:35 by ccariou           #+#    #+#             */
/*   Updated: 2023/02/07 12:22:25 by ccariou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"
const unsigned int page_size = PAGE_SIZE;

static t_path *find_path(t_info *info, t_queueitem *start)
{
	t_queueitem *current_item;
	t_path		*new_path;
	int 		path_idx;
	static int	path_count;

	new_path = open_path(info, start->steps + 1);
	path_idx = start->steps;
	new_path->arr[path_idx--] = info->end;
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
	return (!check_bitmask_idx(&current_item->rooms_used, link_to->number));
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
		set_bitmask_idx(&current_item->rooms_used, current_room->number);
		current_link = current_room->link_head;
		while (current_link != NULL)
		{
			if (current_link->link_to == info->end)
			{
	//			printf("queue len when path found: %d\n", queue->len);
				return (find_path(info, current_item));
			}
			if (can_add_to_queue(current_item, current_link->link_to))
				add_to_queue(&queue, current_link->link_to, current_item);
			current_link = current_link->next;
		}
	}
	return (0);
}


int	solve(t_info *info)
{	
	static t_queue		queue;
	t_pathgroup	*groups;
	t_path		*next_path;
	int			round;

	round = 1;
	//#TODO should path container be dynamic?
	groups = get_groups();
	printf("********SOLVE******\n");
	open_queue(&queue, info->start);
	printf("ants = %d\n", info->ants);
	while (info->total_paths < info->ants)
	{
		printf("\nROUND %d, total_paths = %d\n", round, info->total_paths);
		next_path = bfs(&queue, info);
		if (!next_path)
		{
			printf("All paths found!\n");
			break ;
		}
		else
			find_groups_for_path(info, next_path, groups);
/*		printf("********path#%d len:%d******\n", next_path->id, next_path->len);
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
		printf("\n");*/
		round++;
	}
	/*
	int group_idx = 0;

	printf("\n******GROUPS, total amount %d*******\n", info->total_groups);
	while (group_idx < info->total_groups)
	{
		t_pathgroup *current_group = (groups + group_idx);
		printf("\n********group#%d, len = %d******\n", current_group->id, current_group->len);
		printf("contains following paths: ");
		for (int i = 0; i < current_group->len; i++)
		{
			printf("(%d, len:%d)", current_group->arr[i]->id, current_group->arr[i]->len);
			if (i < current_group->len - 1)
				printf(" ");
		}
		printf("\n");
		printf("uses following rooms:\n");
		print_bitmask(&current_group->room_mask);
		group_idx++;
	}
	*/
	printf("teub a l'air, groups %d\n", info->total_groups);
	return (info->total_groups);
}
