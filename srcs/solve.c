/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccariou <ccariou@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 16:47:35 by ccariou           #+#    #+#             */
/*   Updated: 2023/01/13 23:04:34 by ccariou          ###   ########.fr       */
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
	int i;

	seek = start;
	i = 0;
	while (seek != end)
	{
		path[i] = (t_link *)malloc(sizeof(t_link));
		path[i]->from = seek->room;
		path[i]->link_to = seek->previous->room;
		seek = seek->previous;
		i++;
	}
	path[i] = (t_link *)malloc(sizeof(t_link));
	path[i]->from = seek->room;
	path[i]->link_to = info->start;

	return (i);
}

static int	bfs(t_queueitem **queue, t_link **path, t_info *info)
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
			if (seek->link_to->visited != 1)
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

t_queueitem	**init_q(t_queueitem **queue, t_info *info)
{
	queue[0] = (t_queueitem *)malloc(sizeof(t_queueitem));
	queue[0]->room = info->start;
	queue[0]->previous = NULL;
	queue[0]->room->visited = 1;
	printf("name of the room in the queue[0]: %s\n", queue[0]->room->id);
	return (queue);
}

int	solve(t_info *info)
{	
	t_queueitem	**queue;
	t_link	**path;
	int i;

//	t_link	*link_path;
//	t_queueitem	**route;
	//TODO give id to each route ? stich them to path struct ?

	printf("********SOLVE******\n");
	queue = (t_queueitem **)malloc(sizeof(t_queueitem *) * (info->rooms + 1));
	path = (t_link **)malloc(sizeof(t_link *) * 42);
	if (!queue || !path)
		return (ERROR);
//	ft_bzero(&route, sizeof(route));
//
	queue = init_q(queue, info);
	i = bfs(queue, path, info);
	printf("********path******\n");
	while (--i >= 0)
	{
		printf("%s -> %s\n", path[i]->link_to->id, path[i]->from->id);
	}
	i = bfs(queue, path, info);
	printf("********path******\n");
	while (--i >= 0)
	{
		printf("%s -> %s\n", path[i]->link_to->id, path[i]->from->id);
	}
	printf("teub a l'air");
//	printf("path link_to == %s\n", path->link_to->id);
//	lem->path_sets = iteration - 1;
//	lem->error += (iteration < 2) * -4;
//	free(queue);
	return (1);
}
