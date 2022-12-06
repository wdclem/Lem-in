/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccariou <ccariou@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 14:57:06 by ccariou           #+#    #+#             */
/*   Updated: 2022/12/06 13:09:39 by ccariou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	validate_info(t_info *info, t_room *room)
{
	int	i;
	int j;

	i = 0;
	j = 0;
	save_map(info);
	while (info->str[j] != NULL)
	{
		printf("map = %s\n", info->str[j]);
		j++;
	}
	i = save_ants(info, i);
//	printf("seg test after save ants\n");
	printf("ants = %d\n", info->ants);
//	printf("i = %d\n", i);
	i = save_rooms(info, room, i);
	j = 0;
	printf("rooms = %d\n", info->rooms);
	while (j < info->rooms)
	{
		printf("room = %d j = %d\n", room->id[j], j);
		j++;
	}
//	i = save_links(info, rooms, i);
}


int	main(int argc, char **argv)
{
	t_info	info;
	t_room room;

	/* INITIALIZE STRUCT TO 0 */
	ft_bzero(&info, sizeof(t_info));
	ft_bzero(&room, sizeof(t_info));
	if (argc < 1 || !argv)
		return (ERROR);
	printf("seg test main\n");
	validate_info(&info, &room);


	return (0);
}
