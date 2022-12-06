/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccariou <ccariou@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 14:59:25 by ccariou           #+#    #+#             */
/*   Updated: 2022/12/06 13:28:37 by ccariou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEMIN_H
# define LEMIN_H

#include "libft.h"
#include <stdio.h> //TODO: TO BE REMOVE

# define ERROR 1
# define ANTS_MAX 2147483647

typedef struct s_info{
	int		ants;
	int		rooms;
	int		start;
	int		end;
	char	**str;
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
	char			id[500];
	size_t			alloced;
} 				t_room;

typedef struct	s_link_id
{
	int	left;
	int	right;
}	t_link_id;

typedef char * t_name;

typedef int	t_bool;

int	main(int argc, char **argv);

/* PARSING/VALIDATION */
int	save_map(t_info *info);
int	save_ants(t_info *info, int i);
int	save_rooms(t_info *info, t_room *rooms, int i);

/* UTIL.C */
int	check_comment(t_info *info, int i);

/*
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
*/
#endif
