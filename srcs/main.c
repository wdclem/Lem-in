/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccariou <ccariou@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 14:57:06 by ccariou           #+#    #+#             */
/*   Updated: 2023/02/06 16:23:39 by ccariou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static int	validate_info(t_info *info, t_hasht *table)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (!info->str[i])
		return (ERROR);
	printf ("content 1\n");
	i = save_ants(info, i);
	printf ("ants = %d\n", info->ants);
	if (!info->str[i])
		return (ERROR);
	i = save_rooms(info, table, i);
	if (!info->str[i])
		return (ERROR);
	i = save_links(info, table, i);
	j++;
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
}

int	main(int argc, char **argv)
{
	t_info	info;
	t_hasht	*table;

	ft_bzero(&info, sizeof(t_info));
	table = table_init();
	if (argc < 1 || !argv)
		return (ERROR);
	save_map(&info);
	if (!validate_info(&info, table))
		print_input(&info);
	printf("content 1\n");
	write(1, "\n", 1);
	solve(&info);
	/*static t_info test_info;
	t_pathgroup **groups = get_pathgroups(&test_info);
	if (groups)
		printf("found groups :)\n");

	printf("group[0] == %d\n", (*groups)->id);//arr[0]->arr[0]->id);
	move_ants2(&info, groups);
		*/
	return (0);
}
