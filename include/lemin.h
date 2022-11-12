/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccariou <ccariou@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 14:59:25 by ccariou           #+#    #+#             */
/*   Updated: 2022/10/12 16:03:56 by ccariou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEMIN_H
# define LEMIN_H

#include "libft.h"
#include <stdio.h> //TODO: TO BE REMOVE

typedef struct s_info{
	int		ants;
	int		*room;
	int		start_room_id;
	int		end_room_id;
}				t_info;

// testing starts

typedef	struct	s_avltree
{
	int					balance;
	struct s_avltree	*left;
	struct s_avltree	*right;
} t_node;

typedef struct	s_room
{
	struct s_room	*links;
	int				link_count;
	size_t			alloced;
} t_room;

typedef struct	s_link_id
{
	int	left;
	int	right;
}	t_link_id;

typedef char * t_name;

typedef int	t_bool;

int	main();
t_info	*get_info(void);


t_room **get_rooms(void);
t_name *get_room_names (void);

int	name_to_id(char *name);
int room_to_id(t_room *room);
t_room *id_to_room(int id);
t_name id_to_name(int id);
t_room	*go_to_next_room(t_room *cur_room, t_link_id *link_id);

void increment_room_count(void);
int get_room_count(void);

t_bool	is_occupied(t_room room);
t_bool	is_visited(t_room room);
int can_read_file(void);

#endif
