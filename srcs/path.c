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
#include "libft.h"

static inline int check_bitmask_idx(t_bitmask *mask, int idx)
{
	return (*mask[idx / (sizeof(long) * 8)] & (1 << (idx % (sizeof(long) * 8))));
}

void print_bitmask(t_bitmask *mask)
{
	for (int i = 0; i < (int)(MASKSIZE * sizeof(long) * 8); i++)
	{
		if (check_bitmask_idx(mask, i))
		{
			printf("PAGE:%lu, ENTRY:%lu (%d)\n", i / (sizeof(long) * 8), i % (sizeof(long) * 8), i);
		}
	}
	printf("\n");
}

static inline void set_bitmask_idx(t_bitmask *mask, int idx)
{
	//printf("before bitmask set\n");
//	print_bitmask(mask);
	//printf("*SET PAGE:%lu, ENTRY:%lu (%d)\n", idx / (sizeof(long) * 8), idx % (sizeof(long) * 8), idx);
	*mask[idx / (sizeof(long) * 8)] |= (1 << (idx % (sizeof(long) * 8)));
//	printf("after bitmask set\n");
//	print_bitmask(mask);
}

void add_room_to_path(t_path **path, t_room *room, int index)
{
	t_room	**ptr;

	if (index > (*path)->len)
		return ;
	ptr = (*path)->arr + index;
	*ptr = room;
//	printf("adding room %s (%d) to path %d\n", (*ptr)->id, (*ptr)->number, (*path)->id);
	set_bitmask_idx(&(*path)->room_mask, room->number);
//	printf("bitmask after adding this room:\n");
	//print_bitmask(&(*path)->room_mask);
}

static int	reserve_path(t_path **path, int len)
{
	t_room	**new_arr;

	new_arr = (t_room **)ft_memalloc(len * sizeof(t_room *));
	if (!new_arr)
		return (0);
	(*path)->arr = new_arr;
	(*path)->len = len;
//	printf("reserved path with len of %d\n", (*path)->len);
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
