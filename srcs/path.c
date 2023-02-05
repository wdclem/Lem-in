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

static int	reserve_path(t_path **path, int len)
{
	t_room	**new_arr;

	new_arr = (t_room **)ft_memalloc(len * sizeof(t_room *));
	if (!new_arr)
		return (0);
	(*path)->arr = new_arr;
	(*path)->len = len;
	return (len);
}

t_path	*open_path(int len)
{
	t_path		*new_path;

	new_path = (t_path *)ft_memalloc(sizeof(t_path));
	if (!new_path)
		return (NULL);
	if (!reserve_path(&new_path, len))
	{
		ft_memdel((void **)new_path);
		return (NULL);
	}
	return (new_path);
}

void	close_path(t_path **path)
{
	ft_memdel((void **)&(*path)->arr);
	ft_memdel((void **)path);
}
