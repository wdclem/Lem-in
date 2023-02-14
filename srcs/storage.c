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

t_path	*get_path_arr(void)
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

t_flowmap *get_stable_flowmap(void)
{
	static t_flowmap	stable_flowmap;

	return (&stable_flowmap);
}

t_flowmap *get_working_flowmap(void)
{
	static t_flowmap	working_flowmap;

	return (&working_flowmap);
}
