/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccariou <ccariou@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 14:59:25 by ccariou           #+#    #+#             */
/*   Updated: 2023/02/03 17:42:44 by ccariou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEMIN_H
# define LEMIN_H

# include "../libft/includes/libft.h"
# include <stdio.h> //TODO: TO BE REMOVE

# define ERROR 1
# define ANTS_MAX 2147483647
# define HT_CAP 2056 // hash table capacity 

typedef struct s_room
{
	//struct s_room	*links; Probably swap for a link struct list
	int				link_count;
	char			*id;
	int				x;
	int				y;
	int				visited;
	int				valid;
	int				free;
	struct s_link	*link_head;
	struct s_room	*next;
	size_t			alloced;
}					t_room;

typedef struct s_link
{
	t_room			*from;
	t_room			*link_to;
	//int				from_used;
	//int				link_to_used;
	//int				cap;
	int				flow;
	struct s_link	*next;
}					t_link;

/* Struct to hold input info */
typedef struct s_info
{
	int				total_links;	
	int				total_paths;
	int				ants;
	int				rooms;
	int				s_check;
	int				e_check;
	char			**str;
	struct s_room	*start;
	struct s_room	*end;
}					t_info;

typedef struct s_queueitem
{
	t_room				*room;
	int					steps;
	struct s_queueitem	*previous;
	struct s_queueitem	*next;
	int					conflict;
}						t_queueitem;

typedef struct s_queue
{
	t_queueitem	*arr;
	int			len;
	int			alloced;
} t_queue;

typedef struct s_path
{
	t_room	**arr;
	int		len;
	int		ants_in;
} t_path;

typedef struct s_hasht
{
	t_room	**room;
}			t_hasht;

typedef	struct	s_ant
{
	int			id;
	t_room		*room;
	t_path		*path;
}				t_ant;

int		main(int argc, char **argv);
int		solve(t_info *info);

/* PARSING/VALIDATION */
int		save_map(t_info *info);
int		save_ants(t_info *info, int i);
int		save_rooms(t_info *info, t_hasht *table, int i);
int		save_links(t_info *info, t_hasht *table, int i);

/* UTIL.C */
t_hasht	*table_init(void);
int		check_comment(t_info *info, int i);
int		check_comment_link(t_info *info, t_hasht *table, int i);
int		dj2b_hash(char *key);
t_room	*pointer_to_room(t_hasht *table, char *id);
t_room	*make_room(char *key, int x, int y);
t_link	*new_link(t_room *from, t_room *link_to);

/* DYNAMIC CONTAINERS */
t_queue	*open_queue(t_room *start, int len);
int		reserve_space_in_queue(t_queue **q, int len);
int		add_to_queue(t_queue **q, t_room *room, t_queueitem *previous);
void	clear_queue(t_queue **q);
void	close_queue(t_queue **q);

/* PRINT OUTUPUT */
int	move_ants(t_info *info, t_path **path);
void test_ant_move(void);


t_path	*open_path(int len);
void	set_path_step(t_path **path, t_link* link, int index);
void	close_path(t_path **path);
#endif
