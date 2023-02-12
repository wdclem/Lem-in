/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_management.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccariou <ccariou@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 15:14:34 by ccariou           #+#    #+#             */
/*   Updated: 2023/02/12 14:36:58 by ccariou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int	error_center(int error_code)
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
		ft_printf("start/end incorrect\n");
	else if (error_code == 5)
		ft_printf("room incorrect\n");
	else if (error_code == 6)
		ft_printf("link incorrect\n");
	return (-1);
}
