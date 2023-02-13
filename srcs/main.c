/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccariou <ccariou@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 14:57:06 by ccariou           #+#    #+#             */
/*   Updated: 2023/02/13 16:14:51 by ccariou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static int	validate_info(t_info *info, t_hasht *table)
{
	int	i;

	i = 0;
	if (!info->str[i])
		return (ERROR);
	i = save_ants(info, i);
	if (i == -1)
		return (ERROR);
	i = save_rooms(info, table, i);
	if (!info->str[i] || i == -1)
		return (error_center(4, table));
	i = save_links(info, table, i);
	if (i == -1)
		return (error_center(5, table));
	return (i);
}

static void	print_input(t_info *info)
{
	int	i;

	i = 0;
	while (info->str[i])
	{
		ft_putstr(info->str[i]);
		write(1, "\n", 1);
		i++;
	}
	ft_freearray((void **)info->str, i);
}

int	main(int argc, char **argv)
{
	t_info		info;
	t_hasht		*table;

	ft_bzero(&info, sizeof(t_info));
	table = table_init();
	if (argc < 1 || argc > 2|| !argv)
		return (error_center(0, table));
	if (save_map(&info) == -1)
		return (0);
	if (validate_info(&info, table) == -1)
		return (0);
	print_input(&info);
	printf("content 1\n");
	write(1, "\n", 1);
	if (solve(&info))
		move_ants2(&info);
	else
		printf("bad map, no paths :(\n");
	return (0);
}
