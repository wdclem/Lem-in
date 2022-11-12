/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccariou <ccariou@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 14:57:06 by ccariou           #+#    #+#             */
/*   Updated: 2022/11/08 13:40:09 by ccariou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	validate_info(t_info *info)
{
	save_map(&info);
	validate_input(&info);
}


int	main(int argc, char **argv)
{
	t_info	info;

	ft_bzero(&info, sizeof(g_info));
	if (argc < 1)
		return (ERROR);


	return (0);
}
