/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpolonen <tpolonen@student.hive.fi>          +#+  +:+       +#+      */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 14:59:25 by tpolonen           #+#    #+#            */
/*   Updated: 2023/01/16 18:30:07 by tpolonen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void add_room_to_path(t_path **path, t_room *room, int index)
{
	t_room	**ptr;

	if (index > (*path)->len)
		return ;
	ptr = (*path)->arr + index;
	*ptr = room;
	set_bitmask_idx(&((*path)->room_mask), room->number);
}

t_path	*open_path(t_info *info, int len)
{
	t_path		*path_arr;
	t_path		*new_path;

	path_arr = get_paths();
	new_path = (path_arr + info->total_paths++);
	new_path->len = len;
	return (new_path);
}
