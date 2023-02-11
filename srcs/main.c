/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccariou <ccariou@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 14:57:06 by ccariou           #+#    #+#             */
/*   Updated: 2023/02/09 13:58:30 by ccariou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static int	validate_info(t_info *info, t_hasht *table)
{
	int	i;
	int	error;

	i = 0;
	error = 0;
	if (!info->str[i])
		return (ERROR);
	printf ("content 1\n");
	while (save_ants(info, i, &error) == 0)
		i++;
	i++;
	printf ("ants = %d\n", info->ants);
	if (!info->str[i] || error)
		return (ERROR);
	i = save_rooms(info, table, i, &error);
	if (!info->str[i] || error)
		return (ERROR);
	i = save_links(info, table, i, &error);
	return (0);
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
	t_info		*info;
	t_hasht		*table;

	info = get_info();
	table = table_init();
	if (argc < 1 || !argv)
		return (ERROR);
	save_map(info);
	if (!validate_info(info, table))
		print_input(info);
	printf("content 1\n");
	write(1, "\n", 1);
	if (solve(info))
		move_ants2(info);
	else
		printf("bad map, no paths :(\n");
	return (0);
}
