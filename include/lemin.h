/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccariou <ccariou@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 14:59:25 by ccariou           #+#    #+#             */
/*   Updated: 2023/01/11 16:11:14 by ccariou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEMIN_H
# define LEMIN_H

#include "libft.h"
#include <stdio.h> //TODO: TO BE REMOVE

# define ERROR 1
# define ANTS_MAX 2147483647
# define HT_CAP 2056 // hash table capacity 

typedef struct s_path
{
	int				*path;
	int				len;
	int				max;
	int				*division;
	int				longest;
	struct s_path	*next;
}	t_path;

typedef struct s_q
{
	int				*q;
	int				*visited;
	int				*prev;
	int				len;
	int				position;
	int				**flow;
}	t_q;

typedef struct	s_room
{
	//struct s_room	*links; Probably swap for a link struct list
	int				link_count;
	char			*id;
	int				x;
	int				y;
	int				visited;
	int				valid;
	struct s_link	*link;
	struct s_room	*next;
	size_t			alloced;
} 				t_room;

typedef struct	s_link
{
	t_room			*from;
	t_room			*link_to;
	int				left;
	int				right;
	int				cap;
	int				flow;
	struct s_link	*next;
	struct s_link	*path_list;
}					t_link;

/* Struct to hold input info */
typedef struct s_info{
	int		total_links;	
	int		ants;
	int		rooms;
	int		s_check;
	int		e_check;
	char	**str;
	struct s_room	*start;
	struct s_room	*end;
}				t_info;

typedef struct s_route
{
	int				id;
	int				len;
	int				set;
	int				ants;
	struct s_path	*path;
	struct s_route	*next;
}	t_route;
/*
** hash table", aka an array of pointers to room 
*/

typedef struct s_hasht
{
	t_room **room;
}	t_hasht;

// testing starts

typedef	struct	s_avltree
{
	int					balance;
	struct s_avltree	*left;
	struct s_avltree	*right;
} t_node;

typedef char * t_name;

typedef int	t_bool;

int	main(int argc, char **argv);
int	solve(t_info *info);

/* PARSING/VALIDATION */
int	save_map(t_info *info);
int	save_ants(t_info *info, int i);
int	save_rooms(t_info *info, t_hasht *table, int i);
int	save_links(t_info *info, t_hasht *table, int i);

/* UTIL.C */
t_hasht	*table_init(void);
int	check_comment(t_info *info, int i);
int	check_comment_link(t_info *info, t_hasht *table, int i);
int dj2b_hash(char *key);
t_room *pointer_to_room(t_hasht *table, char *id);
t_room	*make_room(char *key,int x, int y);
t_link	*new_link(t_room *from, t_room *link_to);

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
