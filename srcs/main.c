/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccariou <ccariou@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 14:57:06 by ccariou           #+#    #+#             */
/*   Updated: 2023/02/15 19:46:32 by ccariou          ###   ########.fr       */
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
		return (error_center(info, 2, table));
	i = save_rooms(info, table, i);
	if (i == -1 || !info->str[i])
		return (error_center(info, 4, table));
	i = save_links(info, table, i);
	if (i == -1 || info->total_links <= 0)
		return (error_center(info, 5, table));
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
	ft_freearray((void ***)&info->str, i);
	info->str = NULL;
}

int	main(int argc, char **argv)
{
	static t_info	info;
	t_hasht			*table;
	t_pathgroup		*best_group;

	table = table_init();
	if (!table)
		return (error_center(&info, 5, table));
	if (argc < 1 || argc > 2 || !argv)
		return (error_center(&info, 0, table));
	if (save_map(&info) == -1)
		return (error_center(&info, 1, table));
	if (validate_info(&info, table) == -1)
		return (0);
	if (info.str)
		print_input(&info);
	best_group = solve(&info);
	if (best_group)
		move_ants(&info, best_group);
	else
		return (error_center(&info, 0, table));
	free_before_exit(&info, table);
	return (0);
}
