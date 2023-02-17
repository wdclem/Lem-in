/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_management.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccariou <ccariou@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 15:14:34 by ccariou           #+#    #+#             */
/*   Updated: 2023/02/13 19:18:35 by ccariou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int	free_str_split(char **str_arr, int count, int error)
{
	ft_freearray((void ***)&str_arr, count);
	return (error);
}

static void	free_links(t_room *room)
{
	t_link	*seek;
	t_link	*previous;

	seek = room->link_head;
	while (seek)
	{
		previous = seek;
		seek = seek->next;
		free(previous);
	}
}

void	free_hashtable(t_hasht *table)
{
	int		i;

	i = 0;
	if (table->room)
	{
		while (i < HT_CAP)
		{
			if (table->room[i])
			{
				free_links(table->room[i]);
				free(table->room[i]->id);
				free(table->room[i]);
			}
			i++;
		}
		free(table->room);
	}
	free(table);
}

void	free_before_exit(t_info *info, t_hasht *table)
{
	if (info->str)
		ft_freearray((void ***)&info->str, MAX_LINES);
	if (table)
		free_hashtable(table);
}

int	error_center(t_info *info, int error_code, t_hasht *table)
{
	if (error_code == 0)
		ft_printf("usage ./lem-in < path/to/file\n");
	else if (error_code == 1)
		ft_printf("Bad input\n");
	else if (error_code == 2)
		ft_printf("Bad input\n");
	else if (error_code == 3)
		ft_printf("Bad input\n");
	else if (error_code == 4)
		ft_printf("Bad input\n");
	else if (error_code == 5)
		ft_printf("Bad input\n");
	else if (error_code == 6)
		ft_printf("Table allocation failed, program stop\n");
	free_before_exit(info, table);
	return (-1);
}
