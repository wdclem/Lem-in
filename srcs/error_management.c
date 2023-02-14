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

/*void	free_before_exit(t_info *info, t_hasht *table)
{
	if (info->str)
		ft_freearray((void **)info->str, i);
	while(table->room[i])
	{
		free(table->room[i]->id);
		i++;
	}
	if (table)
		free(table);
		*/

int	error_center(int error_code, t_hasht *table)
{
	if (error_code == 0)
		ft_printf("usage ./lem-in < path/to/file\n");
	else if (error_code == 1)
		ft_printf("empty file/file incorrect\n");
	else if (error_code == 2)
		ft_printf("ants number incorrect\n");
	else if (error_code == 3)
		ft_printf("'L' in room name\n");
	else if (error_code == 4)
		ft_printf("room incorrect\n");
	else if (error_code == 5)
		ft_printf("link incorrect\n");
	if (table)
		free(table);
//	free_before_exit;
	return (-1);
}
