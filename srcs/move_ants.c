/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_ants.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccariou <ccariou@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 09:43:23 by ccariou           #+#    #+#             */
/*   Updated: 2023/02/03 11:24:15 by ccariou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

/*
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
	}
	return (array);
}
*/
int	move_ants(t_info *info, t_path **path)
{
	int	i;
	int	j;
	t_ant	**ants;
//	char	*result;

	i = 0;
	j = 0;
	while(path)
	{
		while (i < path[i]->len)
		{
			printf("%s -> %s", path[i]->arr[j]->from->id, path[i]->arr[j]->link_to->id);
			j += 1;
			if (i < path[i]->len)
				printf(", ");
			else
				printf("]\n");
		}
		i++;
	}
	ants = NULL;
	ants = (t_ant **)malloc(sizeof(t_ant *) * info->ants);
	ants = ants_array(info, ants);
	while(i < info->ants)
	{
		printf("array[i] == %d\n", ants[i]->id);
		i++;
	}
	return(0);
}
