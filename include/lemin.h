/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccariou <ccariou@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 14:59:25 by ccariou           #+#    #+#             */
/*   Updated: 2023/02/09 14:15:28 by ccariou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEMIN_H
# define LEMIN_H

# include "../libft/includes/libft.h"
# include <stdio.h> //TODO: TO BE REMOVE

# define ERROR 1
# define ANTS_MAX 8192
# define HT_CAP 65536 // hash table capacity 
# define MAX_ROOMS 8192
# define MAX_GROUP_SIZE 256 
# define MAX_PATHS 1024 
# define MAX_PATH_SIZE 2048
# define MAX_QUEUE 8192
# define MAX_GROUPS 512 
# define MAX_LINKS 256
# define MAX_ROOM_PAGES (MAX_ROOMS / (sizeof(unsigned int)))
# define MAX_LINK_PAGES (MAX_LINKS / (sizeof(unsigned int)))
# define PAGE_SIZE (sizeof(unsigned int) * 8)

typedef struct s_room
{
	unsigned short	link_count;
	char			*id;
	unsigned short	number;
	unsigned short	x;
	unsigned short	y;
	char			valid;
	char			occupied;
	struct s_link	*link_head;
	size_t			alloced;
}					t_room;

typedef struct s_link
{
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

typedef struct s_roommask
{
	unsigned int	bits[MAX_ROOM_PAGES];
	unsigned short	last_page;
}					t_roommask;

typedef struct s_linkmask
{
	unsigned int	bits[MAX_LINK_PAGES];
	unsigned char	last_page;
}					t_linkmask;

typedef struct s_queueitem
{
	t_room				*room;
	struct s_queueitem	*previous;
	unsigned short		steps;
}						t_queueitem;

typedef struct s_queue
{
	t_queueitem	arr[MAX_QUEUE];
	int			top;
	t_roommask	rooms_used;
} t_queue;

typedef	struct	s_flowitem
{
	t_linkmask	flow_in;
	t_linkmask	flow_out;
	t_linkmask	blocked;
} t_flowitem;

typedef struct	s_flowmap
{
	t_flowitem	arr[MAX_ROOMS];
} t_flowmap;

typedef struct s_path
{
	unsigned short	id;
	unsigned short	len;
	t_room			*arr[MAX_PATH_SIZE];
	t_roommask		room_mask;
	t_roommask		groups;
	unsigned short	group_count;
	unsigned short	ants_in;
}				t_path;

typedef struct s_pathgroup
{
	unsigned short	id;
	unsigned short	len;
	t_path			*arr[MAX_GROUP_SIZE];
	t_roommask		room_mask;
	unsigned short	total_path_len;
	unsigned short	ants_in;
}				t_pathgroup;

typedef struct s_ant
{
	int			id;
	t_room		*room;
	t_path		*path;
	int			path_idx;
}				t_ant;

int			main(int argc, char **argv);
int			solve(t_info *info);

/* PARSING/VALIDATION */
int			save_map(t_info *info);
int			save_ants(t_info *info, int i, int *error);
int			save_rooms(t_info *info, t_hasht *table, int i, int *error);
int			save_links(t_info *info, t_hasht *table, int i, int *error);

/* UTIL.C */
int			set_table(t_info *info, t_hasht *table, char *room_key);
int			check_comment_for_start_and_end(t_info *info, int i);
int			check_comment_link(t_info *info, t_hasht *table, int i);
int			dj2b_hash(char *key);
t_room		*pointer_to_room(t_hasht *table, char *id);

/* INIT.C */
t_hasht		*table_init(void);
t_room		*make_room(t_info *info, char *key);
t_link		*new_link(t_room *from, t_room *link_to);
t_ant		**ants_array(t_info *info, t_ant **array);
t_ant		*init_ant(t_info *info, int *id);

/* QUEUE */
void		queue_open(t_queue *queue, t_room *start);
int			queue_add_item(t_queue **queue, t_link *room, t_queueitem *previous);
void		queue_clear(t_queue **queue);

/* FLOWMAP */
void		flow_update_map(void);
void		flow_update_room(int room_id, int in_link_id, int out_link_id);
void		flow_block_link(int room_id, int link_id);
int			flow_allows_movement(int room_id);
int			flow_forces_movement(t_queue *queue, t_queueitem *current_item);

/* GROUPING */
void		pathgroup_place_path(t_info *info, t_path *path,
				t_pathgroup *groups);

/* PRINT OUTUPUT */
int			move_ants2(t_info *info);

/* PATHS */
t_path		*path_open(t_info *info, int len);
void		path_add_room(t_path **path, t_room *room, int index);
t_path 		*path_find_next(t_info *info, t_queueitem *start);

/* BITMASK */
int			check_bitmask_idx(t_roommask *mask, int idx);
void		print_bitmask(t_roommask *mask);
void		set_bitmask_idx(t_roommask *mask, int idx);
void		add_bitmask(t_roommask *src, t_roommask *dst);
int			maskcmp(t_roommask *left, t_roommask *right);

/* STORAGE */
t_path		*get_paths(void);
t_pathgroup	*get_groups(void);
t_queue		*get_queue(void);
t_flowmap	*get_flowmap(void);

#endif
