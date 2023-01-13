/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccariou <ccariou@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 16:47:35 by ccariou           #+#    #+#             */
/*   Updated: 2023/01/13 14:54:01 by ccariou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

/*
t_room	**add_to_route(t_room **q)
{
*/

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


static int	bfs(t_room **q, t_info *info)
{
	t_room	*tmp;
//	t_link	*tmp2;

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
//				add_to_route(q);
/*				if (tmp->link)
				{
					tmp2 = *link_path;
					*link_path = tmp->link;
					(*link_path)->path_list = tmp2;

				}*/
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
//	t_link	*link_path;
//	t_room	**route;
	//TODO give id to each route ? stich them to path struct ?

	printf("********SOLVE******");
	q = (t_room **)malloc(sizeof(t_room *) * (info->rooms + 1));
	if (!q)
		return (ERROR);
//	ft_bzero(&route, sizeof(route));
	while (q)
	{
//		link_path = NULL;
		q = init_q(q, info);
		if (!bfs(q, info))
			break;
//		while(route)
//			route = route->next;
//		save_route(info, route, link_path);
	}
	printf("teub a l'air");
//	printf("path link_to == %s\n", path->link_to->id);
//	lem->path_sets = iteration - 1;
//	lem->error += (iteration < 2) * -4;
//	free(queue);
	return (1);
}
