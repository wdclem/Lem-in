/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccariou <ccariou@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 14:57:06 by ccariou           #+#    #+#             */
/*   Updated: 2023/01/06 07:04:06 by ccariou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static int	validate_info(t_info *info, t_hasht *table)
{
	int	i;
	int j;

	i = 0;
	j = 0;
	if(!info->str[i])
		return(ERROR);
	printf("content 1\n");
	i = save_ants(info, i);
	printf("ants = %d\n", info->ants);
	if(!info->str[i])
		return(ERROR);
	i = save_rooms(info, table, i);
	if(!info->str[i])
		return(ERROR);
	i = save_links(info, table, i);
	j++;
/*	while (j < info->rooms)
	{
		printf("room = %d j = %d\n", room->id[j], j);
		j++;
	}
	i*/
	return (0);
}


int	main(int argc, char **argv)
{
	t_info	info;
	t_hasht	*table;

	/* INITIALIZE STRUCT TO 0 */
	ft_bzero(&info, sizeof(t_info));
	table =	table_init();
	if (argc < 1 || !argv)
		return (ERROR);
	save_map(&info);
	validate_info(&info, table);
	printf("content 1\n");
	solve(&info);
	return (0);
}
