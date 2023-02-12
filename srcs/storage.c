/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   storage.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccariou <ccariou@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 14:59:25 by ccariou           #+#    #+#             */
/*   Updated: 2023/02/09 12:19:57 by ccariou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

t_path	*get_paths(void)
{
	static t_path	paths_arr[MAX_PATHS];

	return ((t_path *)paths_arr);
}

t_pathgroup	*get_groups_arr(void)
{
	static t_pathgroup	groups_arr[MAX_GROUPS];

	return ((t_pathgroup *)groups_arr);
}

t_queue	*get_queue(void)
{
	static t_queue	queue;

	return (&queue);
}
