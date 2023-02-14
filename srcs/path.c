/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpolonen <tpolonen@student.hive.fi>          +#+  +:+       +#+      */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 14:59:25 by tpolonen           #+#    #+#            */
/*   Updated: 2023/02/09 12:17:31 by ccariou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	path_add_room(t_path **path, t_room *room, t_link *link, int index)
{
	t_room	**room_ptr;
	t_link	**link_ptr;

	room_ptr = (*path)->room_arr + index;
	link_ptr = (*path)->link_arr + index;
	*room_ptr = room;
	*link_ptr = link;
	bitmask_set_idx(&((*path)->rooms_used), room->number);
}

t_path	*path_open(t_info *info, int len)
{
	t_path		*path_arr;
	t_path		*new_path;

	path_arr = get_path_arr();
	new_path = (path_arr + info->total_paths++);
	new_path->len = len;
	return (new_path);
}

t_path *path_make_next(t_info *info, t_queueitem *start)
{
	t_queueitem *current_item;
	t_path		*new_path;
	int 		path_idx;
	static int	path_count;

	new_path = path_open(info, start->steps + 1);
	path_idx = 0;
	new_path->id = path_count++;
	current_item = start;
	while (path_idx < start->steps + 1)
	{
		path_add_room(&new_path, current_item->room, current_item->link_used, \
				path_idx);
		current_item = current_item->previous_item;
		path_idx += 1;
	}
	return (new_path);
}
