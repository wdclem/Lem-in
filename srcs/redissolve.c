/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccariou <ccariou@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 15:06:16 by ccariou           #+#    #+#             */
/*   Updated: 2023/01/11 16:05:14 by ccariou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"


int				gfp(int *p)
{
	return (*p);
}

static void		visit(int visiting, t_rooms *rooms)
{
	rooms->paths[visiting][visiting] = rooms->paths[visiting][visiting] | 1;
}

void			get_room_pointers(int *room_pointers, t_rooms *rooms)
{
	int	i;

	i = 0;
	while (i < rooms->num_of_rooms)
	{
		room_pointers[i] = i;
		i++;
	}
}

static t_list	*get_augmenting_path(t_rooms *rooms, int start, int end,
				int *room_pointers)
{
	t_list	*path;
	t_queue	*to_visit;
	t_list	*i;
	int		room;
	t_list	*connecting_rooms;

	iap(&to_visit, start, room_pointers, rooms);
	while (!is_empty(to_visit))
	{
		room = pop_to_visit(to_visit);
		connecting_rooms = get_connecting_rooms(room, rooms, end);
		i = connecting_rooms;
		while (i)
		{
			if (gfp((int *)i->content) != end || room_pointers[end] == end)
				room_pointers[gfp((int *)i->content)] = room;
			visit(gfp((int *)i->content), rooms);
			push(to_visit, new_list(gfp((int *)i->content)));
			i = i->next;
		}
		ft_lstdel(&connecting_rooms, &delete_generic);
	}
	path = get_path(rooms, end, room_pointers);
	free(to_visit);
	return (path);
}

t_box	*get_paths(t_info *info)
{
	t_path	*paths;
	t_box	*paths_list;
	t_box	*ta;
	int		*room;

	info->paths[start][start] = 1;
	paths = new_t_queue();
	remove_ste_connections(paths, rooms, start, end);
	room_pointers = (int *)malloc(sizeof(int) * rooms->num_of_rooms);
	get_room_pointers(room_pointers, rooms);
	while ((ta = get_augmenting_path(rooms, start, end, room_pointers))
			!= NULL)
	{
		push(paths, ta);
		remove_visited(rooms, start);
	}
	free(room_pointers);
	paths_list = peek(paths);
	free(paths);
	return (paths_list);
}

int	solve(t_info *info)
{
	t_queue	*q;
	t_box	*paths;

	if (!info->ants)
		return ;
	paths = get_paths(info);
	sort_paths(&paths);
	find_path_capacity(paths, ants);
	write_paths_file(paths, rooms);
	return(0);
}
