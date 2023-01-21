/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_ants.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccariou <ccariou@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 09:43:23 by ccariou           #+#    #+#             */
/*   Updated: 2023/01/21 15:11:42 by ccariou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

/*
int		ant_move(t_info *info, t_ant ***ant)
{
	if ((*ant)->path->next->room->free == 0)
	{
		(*ant)->path->room->free= 0;
		(*ant)->path = (*ant)->path->next;
		if ((*ant)->path->room != info->end)
			(*ant)->path->room->occupied = 1;
		return (1);
	}
	else
		return (0);
}
*/

t_ant	*init_ant(t_info *info, int *id)
{
	t_ant *ant;

	ant = (t_ant *)malloc(sizeof(t_ant));
	ant->room = info->start;
	ant->id = (*id)++;
	return(ant);
}

t_ant	**ants_array(t_info *info, t_ant **array)
{
	int		i;
	int		id;
//	int		count;
//	t_ant	*ants;

	i = 0;
	id = 1;
	printf("info->ants == %d\n", info->ants);
	while (i < info->ants)
	{
		array[i] = init_ant(info, &id);
		printf("array[i] add \n");
		i++;
	}
	printf("array created\n");
	return(array);
}

/* TODO save path set in info */
/*
t_array	*assign_ant(t_ant **array, t_path **path)
{
	int		i;

	i = 0;
	while (array)
	{
		while (paths && paths[i]->len + paths[i]->ants_amount >=
							paths[i]->len + paths[i]->ants_amount)
			paths = paths->next;
		if (paths->size > 2)
			paths->ants_amount++;
		array[i]->paths->path;
	}
	return (array);
}
*/
int	move_ants(t_info *info, t_path *path)
{
	int	i;
	t_ant	**ants;
//	char	*result;

	i = 0;
	ants = NULL;
	ants = (t_ant **)malloc(sizeof(t_ant *) * info->ants);
	ants = ants_array(info, ants);
	while(i < info->ants)
	{
		printf("array[i] == %d\n", ants[i]->id);
		i++;
	}
	/*
	assign_ant(info, array);
	print(array)
	*/
	/*
	while (first)
	{
		ants = first;
		while (ants)
		{
			if (ant_move_through_path(&ants, *farm))
				ft_printf("L%d-%s ", ants->number, ants->path->room->name);
			if (ants->path->room == (*farm)->end)
			{
				if (ants == first)
					first = ants->next;
				remove_ant(&first, &ants);
			}
			else
				ants = ants->next;
		}
		ft_printf("\n", moves++);
	}
	(*farm)->moves_done = moves;
	*/
	return(0);
}
