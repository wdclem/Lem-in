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
	//printf("%s -> %s\n", cur->room->id, link_to->id);
	return (q[i]);
}

int	can_find_path(t_queueitem *start, t_queueitem *end, t_path *path)
{
	t_queueitem *seek;
	t_link		*current_link;
	int 		i;

	seek = start;
	current_link = NULL;
	i = 0;

	while (seek->previous && seek != end)
	{
		current_link = seek->room->link_head;
		while (current_link->from != seek->previous->room && current_link->link_to != seek->previous->room )
		{
			current_link = current_link->next;
			if (current_link == NULL)
				return (0);
		}
		current_link->flow += 1;
		path->arr[i] = current_link;
		seek = seek->previous;
		i++;
	}
	path->len = i;
	//printf("hello!!!!\n");
	return (1);
}

static int	bfs(t_queueitem **queue, t_path *path, t_info *info, int round)
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
		//printf("current room name = %s\n", current_room->id);
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
						return (can_find_path(new, queue[0], path));
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
	return (queue);
}

int	solve(t_info *info)
{	
	t_queueitem	**queue;
	t_path		*path;
	int			round;

	//TODO wipe queueue

	round = 1;
	printf("********SOLVE******\n");
	path = (t_path *)malloc(sizeof(t_path));
	ft_bzero(path, sizeof(t_path));
	path->arr = (t_link **)malloc(sizeof(t_link *) * 42);
	ft_bzero(path->arr, sizeof(t_link *) * 42);
	queue = (t_queueitem **)malloc(sizeof(t_queueitem *) * (info->rooms + 1));
	if (!queue || !path)
		return (ERROR);

	printf("ants = %d\n", info->ants);
	while (info->total_paths < info->ants)
	{
		printf("\nROUND %d, total_paths = %d\n", round, info->total_paths);
		queue = init_q(queue, info, round);
		if (bfs(queue, path, info, round) == 0)
		{
			printf("All paths found!\n");
			break ;
		}
		else
			info->total_paths += 1;
		int i = path->len - 1;
		printf("********path, len = %d******\n[", path->len);
		while (i >= 0)
		{
			printf("%s -> %s", path->arr[i]->from->id, path->arr[i]->link_to->id);
			i -= 1;
			if (i >= 0)
				printf(", ");
			else
				printf("]\n");
		}
		round++;
		if (round > 4)
			break ;
	}
	printf("teub a l'air\n");
//	send_ants(info, path);
//	printf("path link_to == %s\n", path->link_to->id);
//	free(queue);
	return (1);
}
