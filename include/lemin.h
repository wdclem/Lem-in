/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccariou <ccariou@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 14:59:25 by ccariou           #+#    #+#             */
/*   Updated: 2023/02/13 16:15:44 by ccariou          ###   ########.fr       */
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
# define MAX_LINKS 18192
# define MAX_QUEUE 12192
# define MAX_PATHS 8192 
# define MAX_PATH_SIZE 8192 
# define MAX_GROUPS 2048 
# define MAX_GROUP_SIZE 8192
# define MAX_PAGES (MAX_ROOMS / (sizeof(unsigned int)))
# define PAGE_SIZE (sizeof(unsigned int) * 8)

# define OPEN 0
# define UPSTREAM 1
# define DOWNSTREAM 2
# define BLOCKED 4

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

typedef struct	s_flowmap
{
	t_flowmask	arr[MAX_LINKS];
} t_flowmap;

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
} t_queue;

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
	unsigned short	score;
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
int			queue_can_be_opened(t_queue *queue, t_flowmap *flowmap, \
				t_info *info);
int			queue_can_add_room(t_queue *queue, t_flowmap *stable_flowmap, \
				t_link *link_to_follow);
void		queue_add_item_and_update_flow(t_queue *queue, t_flowmap *flowmap,
				t_link *link_to_follow, t_queueitem *previous);
void		queue_add_item(t_queue **queue, t_room *next_room, \
				t_link *link_used, t_queueitem *previous);
void		queue_clear(t_queue **queue);

/* FLOWMAP */
const		char *flow_to_str(t_flowmask flow);
void		flowmap_debug_print(t_flowmap *flowmap, int count);
void		flowmap_update_stable_map(t_queueitem *sink, t_flowmap *working, \
				t_flowmap *stable, int total_links);
t_path		*flowmap_paths_remain(t_queue *queue, t_flowmap *flowmap, \
				t_info *info, int *i);
int			flowmap_forces_movement(t_queue *queue, t_info *info, t_queueitem *current_item);

/* GROUPING */
int			grouping_score_group(t_info *info, t_pathgroup *group);
void		grouping_add_path_to_group(t_info *info, t_pathgroup *group, t_path *path);
void		grouping_optimize_pathgroup(t_queue *queue, t_info *info, t_pathgroup *group);

/* PRINT OUTUPUT */
int			move_ants2(t_info *info);

/* PATHS */
t_path		*path_open(t_info *info, int len);
void		path_add_room(t_path **path, t_room *room, t_link *link, int index);
t_path 		*path_make_next(t_info *info, t_queueitem *start);

/* BITMASK */
void 		bitmask_debug_print(t_bitmask *mask);
int			bitmask_check_idx(t_bitmask *mask, int idx);
void		bitmask_set_idx(t_bitmask *mask, int idx);
void		bitmask_clear(t_bitmask *mask);
void 		bitmask_add(t_bitmask *src, t_bitmask *dst);
void 		bitmask_remove(t_bitmask *src, t_bitmask *dst);
int 		bitmasks_are_equal(t_bitmask *left, t_bitmask *right);
int 		bitmasks_share_bits(t_bitmask *left, t_bitmask *right);
void 		bitmask_clear_idx(t_bitmask *mask, int idx);

/* ERROR MANAGEMENT*/
int			error_center(int error_code, t_hasht *table);

/* STORAGE */
t_path		*get_path_arr(void);
t_pathgroup	*get_groups_arr(void);
t_queue		*get_queue(void);
t_flowmap	*get_working_flowmap(void);
t_flowmap	*get_stable_flowmap(void);

#endif
