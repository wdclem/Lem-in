/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccariou <ccariou@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 16:48:20 by ccariou           #+#    #+#             */
/*   Updated: 2023/01/06 03:23:48 by ccariou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

/*
 *probably need to do a list of path so can add a path to list of path
 path = list of room
 routes = list of path
static void	add_to_path(t_room **queue)
{
	int	i;


	i = 0;
	while as long as room == info->end
*/
/*
t_queue	*create(t_room *room)
{
	t_queue	*new;

	new = (t_queue *)malloc(sizeof(t_queue));
	if (new)
	{
		new->room = room;
		new->next = NULL;
	}
	return (new);
}
*/
static void	add_to_queue(t_queue *q, t_queue *tmp)
{
	t_queue	*head;

	// TODO WHILE q->room links q->next->room = links of q->room
	head = tmp;
	while (tmp->room != NULL)
	{
		printf("room in add queue= %s\n", tmp->room->id);
		if (tmp->room == tmp->room->link->link_to)
			return;
		if (tmp->next)
			tmp = tmp->next;
		else
			break;
	}
	q->room = head->room->link->link_to;
//	q->next = create(q->room->link->link_to);
	printf("next room in add queue= %s\n", q->room->id);
	/*
	while (i < q->room->link_count)
	{
		if (tmp->visited = 1);
		tmp = q->room->link 
		if (tmp == q->next->room->id)
			return ;
		else
		{
			q->next = (t_queue *)malloc(sizeof(t_queue));
			q->next = q->room->link->link_to;
		}
		printf("tmp = %s\n", tmp->id);
	}
	q->next->room  = room;
	printf("room = %s\n", q->next->room->id);
//	printf("queue = %s\n", &queue[0]->id);
//	*/
}
/*
** prepends @edge to the front of @path
*/
/*
static void	search_edge_prepend(t_edge **search_edges, t_edge *edge)
{
	t_edge	*tmp;

	if (edge)
	{
		{
			printf("%d ", q->items[i]);
		}
	}
}
	}
}
*/
static int	bfs(t_info *info, t_queue *q)//, t_path **route)
{
//§	t_room 	*room;
//	t_link	*link; 
	t_queue	*tmp;
	t_queue	*tail;

//	room = NULL; 
//	tail = q;
//	q->room->visited = run; // TODO REMOVE WHEN BFS IN WHILE LOOP
//	route = NULL;
	while (q->room != NULL)
	{
		tmp = q;
		q->next = (t_queue *)malloc(sizeof(t_queue));
		q = q->next;
//		printf("link 0 = %s\n", q->room->link->from->id);
//		printf("link 1 = %s\n", q->room->link->next_adjacent->link_to->id);
		printf("room id= %s\n", tmp->room->link->link_to->id);
//		printf("room[0]link->id= %s\n", link->link_to->id);
//		printf("room[0]link->id= %s\n", link->link_to->id);
		while (tmp->room->link != NULL)
		{
			if (tmp->room->link->link_to->visited != 1 && tmp->room->link->has_cap)
			{
				tmp->room->link->link_to->visited= 1; //TODO == visited
				add_to_queue(q, tmp);
//				printf("queue [0] = %s\n", q->room->id);
//				printf("tail = %s\n", tail->room->id);
//				printf("head = %s\n", head->room->id);
//				add_to_path(
//				printf("queue = %s\n", queue[1]->id);
				printf("end checker : link_to = %s, end = %s\n", q->room->link->from->id, info->end->id);
				if (q->room->link->link_to == info->end)
					return (1);
			}
			tmp->room->link = q->room->link->next_adjacent;
//			printf("*2*room[0]link->id= %s\n", link->next_adjacent->link_to->id);
		}
		if (q)
			tail = q;
		printf("head = %s\n", tail->room->id);
		printf("queue = %s\n", q->room->id);
	}
	return (0);
}
static t_queue *init_queue(t_info *info, t_queue *q)
{
	q->room = info->start;
//	q->room->visited = 1;
	return (q);
}
int	solve(t_info *info)
{
	t_queue	*q;
//	t_path	*route;
	int		run;

	run = 1;
//	route = NULL;
//	path = new_route(run);
	printf("*****SOLVE*****\n");
//	printf("room[0]link->id= %s\n", info->start->link->link_to->id);
	q = (t_queue *)malloc(sizeof(t_queue));
	while (q)
	{
		q = init_queue(info, q);
		printf("queue->room->id = %s\n", q->room->id);
//		if (bfs(info, q) == 1)
//			break;
		bfs(info, q);//, &route);
		printf("2eme BFS");
		bfs(info, q);//, &route);
		break;
//		printf("run = %d, queue[0] = %s, queue[1] = %s\n", run, q->room->id, q->next->room->id);
	}
//	if (!bfs(info, queue, &bfs_edges, iteration))
//		break ;
//
//	send_flow(bfs_edges, lem);
//	store_paths(route, lem, iteration);
	run++;
//	printf("run = %d, queue[2] = %s, queue[3] = %s\n", run, q[2].id, q[3].id);
	/*
	lem->path_sets = iteration - 1;
	lem->error += (iteration < 2) * -4;
	free(queue);
	return (route);
	run_paths(info);
	do one path
		if path
			continue;
	*/
	return(0);
}
