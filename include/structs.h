/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccariou <ccariou@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 14:59:25 by ccariou           #+#    #+#             */
/*   Updated: 2023/02/13 16:15:44 by ccariou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "../libft/includes/libft.h"
# include "defines.h"

typedef struct s_room
{
	unsigned short	link_count;
	char			*id;
	unsigned short	number;
	int				occupied;
	int				valid;
	int				distance;
	struct s_link	*link_head;
	size_t			alloced;
}					t_room;

typedef struct s_link
{
	unsigned short	number;
	t_room			*from;
	t_room			*link_to;
	struct s_link	*next;
}					t_link;

/* Struct to hold input info */
typedef struct s_info
{
	int				total_links;	
	int				total_paths;
	int				total_groups;
	int				ants;
	int				rooms;
	int				s_check;
	int				e_check;
	char			**str;
	int				total_strs;
	struct s_room	*start;
	struct s_room	*end;
}					t_info;

typedef struct s_hasht
{
	t_room	**room;
}			t_hasht;

typedef struct s_bitmask
{
	unsigned short	last_page;
	unsigned int	bits[MAX_PAGES];
}					t_bitmask;

typedef char	t_flowmask;

typedef struct s_flowmap
{
	t_flowmask	arr[MAX_LINKS];
}	t_flowmap;

typedef struct s_queueitem
{
	t_room				*room;
	struct s_queueitem	*previous_item;
	t_link				*link_used;
	unsigned short		steps;
	int					was_forced_to_move;
}						t_queueitem;

typedef struct s_queue
{
	t_queueitem	arr[MAX_QUEUE];
	int			top;
	t_bitmask	rooms_used;
	t_bitmask	path_rooms_used;
}	t_queue;

typedef struct s_path
{
	unsigned short	id;
	unsigned short	len;
	t_room			*room_arr[MAX_PATH_SIZE];
	t_link			*link_arr[MAX_PATH_SIZE];
	t_bitmask		rooms_used;
	unsigned short	ants_in;
}				t_path;

typedef struct s_pathgroup
{
	unsigned short	id;
	unsigned short	len;
	t_path			*arr[MAX_GROUP_SIZE];
	t_bitmask		rooms_used;
	unsigned short	total_path_len;
	unsigned short	ants_in;
	double			score;
}				t_pathgroup;

typedef struct s_ant
{
	int			id;
	t_room		*room;
	t_path		*path;
	int			path_idx;
}				t_ant;

#endif
