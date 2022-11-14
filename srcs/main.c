/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccariou <ccariou@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 14:57:06 by ccariou           #+#    #+#             */
/*   Updated: 2022/11/14 16:24:58 by ccariou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	validate_info(t_info *info, t_room *rooms)
{
	save_map(info);
	save_ants(info);
	save_rooms(info, rooms);
	save_links(info, rooms);
}


int	main(int argc, char **argv)
{
	t_info	info;
	t_room rooms;

	ft_bzero(&info, sizeof(g_info));
	ft_bzero(&rooms, sizeof(g_info));
	if (argc < 1)
		return (ERROR);
	validate_info(&info, &rooms);


	return (0);
}
