/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccariou <ccariou@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 14:59:25 by ccariou           #+#    #+#             */
/*   Updated: 2023/02/12 18:45:21 by ccariou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEMIN_H
# define LEMIN_H

# include "../libft/includes/libft.h"
# include <stdio.h> //TODO: TO BE REMOVE

# define ERROR -1
# define ANTS_MAX 8192
# define HT_CAP 65536 // hash table capacity 
# define MAX_ROOMS 8192
# define MAX_GROUP_SIZE 256 
# define MAX_PATHS 1024 
# define MAX_PATH_SIZE 2048
# define MAX_QUEUE 16384
# define MAX_GROUPS 512 
# define MAX_PAGES (MAX_ROOMS / (sizeof(unsigned int)))
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

typedef struct s_bitmask
{
	unsigned int	bits[MAX_PAGES];
	unsigned short	last_page;
}					t_bitmask;

typedef struct s_queueitem
{
	t_room				*room;
	unsigned short		steps;
	signed short		times_used;
	struct s_queueitem	*previous;
	t_bitmask			rooms_used;
}						t_queueitem;

typedef struct s_queue
{
	t_queueitem		arr[MAX_QUEUE];
	signed short	top;
} t_queue;

typedef struct s_path
{
	unsigned short	id;
	t_room			*arr[MAX_PATH_SIZE];
	unsigned short	len;
	t_bitmask		room_mask;
	t_bitmask		groups;
	unsigned short	group_count;
	unsigned short	ants_in;
}				t_path;

typedef struct s_pathgroup
{
	t_path			*arr[MAX_GROUP_SIZE];
	unsigned short	len;
	unsigned short	id;
	t_bitmask		room_mask;
	unsigned short	ants_in;
	unsigned short	total_path_len;
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
int			save_ants(t_info *info, int i);
int			save_rooms(t_info *info, t_hasht *table, int i);
int			save_links(t_info *info, t_hasht *table, int i);

/* UTIL.C */
int			set_table(t_info *info, t_hasht *table, char *room_key);
int			check_comment_for_start_and_end(t_info *info, int i);
int			check_comment_link(t_info *info, t_hasht *table, int i);
int			dj2b_hash(char *key);
int			unique_id(int id, t_hasht *table, char *room_name);
t_room		*pointer_to_room(t_hasht *table, char *id);

/* INIT.C */
t_hasht		*table_init(void);
t_room		*make_room(t_info *info, char *key);
t_link		*new_link(t_room *from, t_room *link_to);
t_ant		**ants_array(t_info *info, t_ant **array);
t_ant		*init_ant(t_info *info, int *id);

/* QUEUE */
void		open_queue(t_queue *queue, t_room *start);
int			add_to_queue(t_queue **queue, t_room *room, t_queueitem *previous);
void		clear_dead_branch_from_queue(t_queueitem *dead_end);
void		garbage_collect(t_queue *queue);
int			next_available_index_to_write(t_queue *queue, int cur_idx);
int			next_available_index_to_read(t_queue *queue, int cur_idx);

/* GROUPING */
void		find_groups_for_path(t_info *info, t_path *path,
				t_pathgroup *groups);
t_pathgroup	**get_pathgroups(t_info *info);

/* PRINT OUTUPUT */
int			move_ants2(t_info *info);
void		test_ant_move(void);

t_path		*open_path(t_info *info, int len);
void		add_room_to_path(t_path **path, t_room *room, int index);
void		close_path(t_path **path);

/* BITMASK */

int			check_bitmask_idx(t_bitmask *mask, int idx);
void		print_bitmask(t_bitmask *mask);
void		set_bitmask_idx(t_bitmask *mask, int idx);
void		add_bitmask(t_bitmask *src, t_bitmask *dst);
int			maskcmp(t_bitmask *left, t_bitmask *right);

/* ERROR MANAGEMENT*/

int	error_center(int error_code);

/* STORAGE */

t_path		*get_paths(void);
t_pathgroup	*get_groups(void);

#endif
