/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccariou <ccariou@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 16:47:35 by ccariou           #+#    #+#             */
/*   Updated: 2023/01/15 18:30:06 by ccariou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

/*
t_room	**add_to_route(t_room **q)
{
*/

t_queueitem	*add_to_q(t_queueitem **q, t_queueitem *cur, t_room *link_to, int size)
{
	int i;

	i = 0;
	while (i < size)
	{
		if (q[i]->room == link_to)
			return (0);
		i++;
	}
	q[i] = (t_queueitem *)malloc(sizeof(t_queueitem));
	q[i]->room = link_to;
	q[i]->previous = cur;
	printf("%s -> %s\n", cur->room->id, link_to->id);
	return (q[i]);
}

int	find_path(t_queueitem *start, t_queueitem *end, t_link **path, t_info *info)
{
	t_queueitem *seek;
	t_link		*current_link;
	int 		i;

	seek = start;
	current_link = NULL;
	i = 0;
	/*
	while (seek != end)
	{
		path[i] = (t_link *)malloc(sizeof(t_link));
		path[i]->from = seek->room;
		path[i]->link_to = seek->previous->room;
		path[i]->link_to->flow = 1;
		seek = seek->previous;
		i++;
	}
	*/
	while (seek != end)
	{
		current_link = seek->room->link_head;
		while (current_link->from != seek->previous->room && current_link->link_to != seek->previous->room )
		{
			current_link = current_link->next;
			if (current_link == NULL)
				return (ERROR);
		}
		seek = seek->previous;
		path
		i++;
	}
	current_link->flow += 1;
	path->links[i] = current_link;
	info->total_paths += 1;

	return (i);
}

static int	bfs(t_queueitem **queue, t_link **path, t_info *info, int round)
{
	t_room	*current_room;
	t_link	*seek;
	t_queueitem *new;
	int queuesize = 1;
	int		i;

	i = 0;
	while (queue[i] != NULL)
	{
		current_room = queue[i]->room;
		printf("current room name = %s\n", current_room->id);
		seek = current_room->link_head;
		while (seek != NULL)
		{
			if (seek->link_to->visited < round && seek->link_to->link_head->flow != 1)
			{
				seek->link_to->visited = 1;
				new = add_to_q(queue, queue[i], seek->link_to, queuesize);
				if (new)
				{
					queuesize++;
					if (seek->link_to == info->end)
					{
						return (find_path(new, queue[0], path, info));
					}
				}
			}
			seek = seek->next;
		}
		i++;
	}
	return (0);
}

t_queueitem	**init_q(t_queueitem **queue, t_info *info, int round)
{
	queue[0] = (t_queueitem *)malloc(sizeof(t_queueitem));
	queue[0]->room = info->start;
	queue[0]->previous = NULL;
	queue[0]->room->visited = round;
	printf("name of the room in the queue[0]: %s\n", queue[0]->room->id);
	return (queue);
}

int	solve(t_info *info)
{	
	t_queueitem	**queue;
	t_path		*path;
	int 	i;
	int		round;

//	t_link	*link_path;
//	t_queueitem	**route;
	//TODO give id to each route ? stich them to path struct ?

	round = 0;
	printf("********SOLVE******\n");
	path = (t_path *)malloc(sizeof(t_path));
	path->links = (t_link **)malloc(sizeof(t_link *) * 42);
	queue = (t_queueitem **)malloc(sizeof(t_queueitem *) * (info->rooms + 1));
	if (!queue || !path)
		return (ERROR);
//	ft_bzero(&route, sizeof(route));
//
	while (info->ants <= info->total_paths)
	{
		queue = init_q(queue, info, round);
		i = bfs(queue, path, info, round);
		printf("path_size == %d\n", info->total_paths);
		printf("********path******\n");
		while (--i >= 0)
		{
			printf("%s -> %s\n", path[i]->link_to->id, path[i]->from->id);
		}
		round++;
	}
	printf("teub a l'air");
//	send_ants(info, path);
//	printf("path link_to == %s\n", path->link_to->id);
//	free(queue);
	return (1);
}
