/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccariou <ccariou@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 16:47:35 by ccariou           #+#    #+#             */
/*   Updated: 2023/01/23 14:10:27 by ccariou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static t_path *find_path(t_queueitem *start)
{
	t_queueitem *current_item;
	t_link		*current_link;
	t_path		*new_path;
	int 		i;

	current_item = start;
	new_path = open_path(start->steps);
	if (!new_path)
		return (NULL);
	current_link = NULL;
	i = start->steps - 1;
	while (i >= 0)
	{
		current_link = current_item->room->link_head;
		while (!(current_link->from == current_item->previous->room || current_link->link_to == current_item->previous->room))
		{
			current_link = current_link->next;
			if (current_link == NULL)
			{
				close_path(&new_path);
				return (0);
			}
		}
		set_path_step(&new_path, current_link, i);
		current_link->flow += 1;
		current_item = current_item->previous;
		i -= 1;
	}
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

#define MAX_PATH 1024

int	solve(t_info *info)
{	
	t_queue		*queue;
	t_path		**paths;
	t_path		*next_path;
	int			round;

	round = 1;
	//#TODO should path container be dynamic?
	paths = (t_path **)ft_memalloc(MAX_PATH * sizeof(t_path *));
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
			paths[info->total_paths] = next_path;
			info->total_paths += 1;
		}
		printf("********path, len = %d******\n[", next_path->len);
		int i = 0;
		while (i < next_path->len)
		{
			//printf("%s -> %s", next_path->arr[i]->from->id, next_path->arr[i]->link_to->id);
			i += 1;
			if (i < next_path->len)
				printf(", ");
			else
				printf("]\n");
		}
		round++;
	}
	printf("teub a l'air\n");
	move_ants(info, paths);
//	send_ants(info, path);
//	printf("path link_to == %s\n", path->link_to->id);
//	free(queue);
	return (1);
}
