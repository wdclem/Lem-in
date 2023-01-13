/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccariou <ccariou@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 02:15:21 by ccariou           #+#    #+#             */
/*   Updated: 2023/01/11 16:47:20 by ccariou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

/*
** stores paths by backtracking from sink to source along the edges that have a
** negative flow, which means its reverse edge must have positive flow. appends
** every new path to the end of a list of paths.
*/

static void	save_route(t_path *route, t_info *info)
{
	t_link	*tmp;

	while(info->end->link)
	{
		while (info->end->link && info->end->link->link_to != info->start)
		{
			if (info->end->link->flow < 0)
			{
//				if (info->end->link->link_to != info->start) already check in 29
//				info->end->link->link_to-> TODO find a way to make work for each iteration
				route->path = path_prepend(route->path, get_rev_edge(edge));
				if (!route->path)
					return (NULL);
				route->len++;
				edge = edge->to->edge;
			}
		else if (edge->src != lem->sink)
			edge = edge->next_adjacent;
		else
			break ;
	}
	if (route->path && route->path->edge->src == lem->source)
		route->is_valid = 1;
	else
		free_path(route->path);
	return (route);

}

static void	update_link(t_link *link)
{
	t_link	*tmp;

	tmp = link->link_to->link;
	while (tmp && tmp->link_to != link->from)
		tmp = tmp->path_list;
	if (tmp)
	{
		link->flow += 1;
		tmp->flow -= 1;
		if (link->flow < link->cap)
			link->cap = 1;
		else
			link->cap = 0;
		if (tmp->flow < tmp->cap)
			tmp->cap = 1;
		else
			tmp->cap = 0;
	}
}

static void	add_flow(t_link *link_path, t_info *info)
{
	t_link	*prev;

	update_link(link_path);
	while (link_path->from != info->start)
	{
		prev = link_path->path_list;
		while (prev->link_to != link_path->from)
		{
			prev = prev->path_list;
		}
		update_link(prev);
		link_path = prev;
	}
}

void	add_to_q(t_room **q, t_room *link_to)
{
	int		i;

	i = 0;
	while (q[i] != NULL)
	{
		if (q[i] == link_to)
			return ;
		i++;
	}
	q[i] = link_to;
}

t_room	*pop(t_room	***q)
{
	t_room	*room;

	if (!(*q)[0])
		return (NULL);
	room = (*q)[0];
	(*q)++;
	return (room);
}


static int	bfs(t_room **q, t_info *info, t_link **link_path)
{
	t_room	*tmp;
	t_link	*tmp2;

	(*q)->visited = 1;
	while (!(*q== NULL))
	{
		tmp = pop(&q);
		printf("tmp == %s\n", tmp->link->link_to->id);
		while (tmp->link != NULL)
		{
			if (tmp->link->link_to->visited != 1 && tmp->link->cap)
			{
				tmp->link->link_to->visited = 1;
				add_to_q(q, tmp->link->link_to);
				if (tmp->link)
				{
					tmp2 = *link_path;
					*link_path = tmp->link;
					(*link_path)->path_list = tmp2;

				}
				printf("tmp->link_to == %s, info->end == %s\n", tmp->link->link_to->id, info->end->id);
				if (tmp->link->link_to == info->end)
					return (1);
			}
			tmp->link = tmp->link->next;
		}
	}
	return (0);
}

t_room	**init_q(t_room **q, t_info *info)
{
	//ft_bzero(&q, sizeof(q));
	q[0] = info->start;
	q[0]->visited = 1;
	return (q);
}

int	solve(t_info *info)
{	
	t_room	**q;
	t_link	*link_path;
	t_path	*route;
	//TODO give id to each route ? stich them to path struct ?
	int		id;

	id = 0;
	printf("********SOLVE******");
	q = (t_room **)malloc(sizeof(t_room *) * (info->rooms + 1));
	route = (t_path *)malloc(sizeof(t_path));
	if (!route)
		return (ERROR);
	ft_bzero(&route, sizeof(route));
	while (q)
	{
		link_path = NULL;
		q = init_q(q, info);
		if (bfs(q, info, &link_path) == 1)
			break;
		add_flow(link_path, info);
		while(route)
			route = route->next;
		save_route(info, route, link_path);
		id++;
	}
	printf("teub a l'air");
//	printf("path link_to == %s\n", path->link_to->id);
//	lem->path_sets = iteration - 1;
//	lem->error += (iteration < 2) * -4;
//	free(queue);
	return (1);
}
