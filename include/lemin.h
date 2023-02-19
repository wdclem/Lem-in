/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccariou <ccariou@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 14:59:25 by ccariou           #+#    #+#             */
/*   Updated: 2023/02/15 18:35:19 by ccariou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEMIN_H
# define LEMIN_H

# include "../libft/includes/libft.h"
# include "structs.h"
# include "defines.h"

/* MAIN LOOP */
int			main(int argc, char **argv);
t_pathgroup	*solve(t_info *info);
void		free_before_exit(t_info *info, t_hasht *table);
void		free_hashtable(t_hasht *table);
int			free_str_split(char **link, int count, int error);

/* PARSING/VALIDATION */
int			save_map(t_info *info);
int			save_ants(t_info *info, int i);
int			save_rooms(t_info *info, t_hasht *table, int i);
int			save_links(t_info *info, t_hasht *table, int i);

/* HELPERS */
int			set_table(t_info *info, t_hasht *table, char *room_key);
int			check_comment_for_start_and_end(t_info *info, int i);
int			check_comment_link(t_info *info, t_hasht *table, int i);
int			link_room_exist(t_hasht *table, char *from, char *link_to);
int			dj2b_hash(char *key);
int			unique_id(int id, t_hasht *table, char *room_name);
int			valid_amount_of_chars_in_room_name(char *name, char c);
t_room		*pointer_to_room(t_hasht *table, char *id);

/* INIT.C */
t_hasht		*table_init(void);
t_room		*make_room(t_info *info, char *key);
t_link		*new_link(t_room *from, t_room *link_to);
int			ants_array(t_info *info, t_ant **array);
t_ant		*init_ant(t_info *info, int *id);

/* QUEUE */
int			queue_can_be_opened(t_queue *queue, t_flowmap *flowmap, \
				t_info *info);
int			queue_can_add_room(t_queue *queue, t_flowmap *stable_flowmap, \
				t_link *link_to_follow, t_flowmask desired_flow);
void		queue_add_item_and_update_flow(t_queue *queue, t_flowmap *flowmap,
				t_link *link_to_follow, t_queueitem *previous);
void		queue_add_item(t_queue **queue, t_room *next_room, \
				t_link *link_used, t_queueitem *previous);
void		queue_clear(t_queue **queue);

/* FLOWMAP */
void		flowmap_update_stable_map(t_queueitem *sink, t_flowmap *working, \
				t_flowmap *stable);
t_path		*flowmap_paths_remain(t_queue *queue, t_flowmap *flowmap, \
				t_info *info, int *i);
int			flowmap_forces_movement(t_queue *queue, t_info *info, \
				t_queueitem *current_item);

/* GROUPING */
int			grouping_score_group(t_info *info, t_pathgroup *group);
void		grouping_add_path_to_group(t_info *info, t_pathgroup *group, \
				t_path *path);
void		grouping_optimize_pathgroup(t_queue *queue, t_info *info, \
				t_pathgroup *group);

/* PRINT OUTUPUT */
int			move_ants(t_info *info, t_pathgroup *best_group);

/* PATHS */
t_path		*path_open(t_info *info, int len);
void		path_add_room(t_path **path, t_room *room, t_link *link, \
				int index);
t_path		*path_make_next(t_info *info, t_queueitem *start);

/* BITMASK */
int			bitmask_check_idx(t_bitmask *mask, int idx);
void		bitmask_set_idx(t_bitmask *mask, int idx);
void		bitmask_clear_idx(t_bitmask *mask, int idx);
void		bitmask_clear(t_bitmask *mask);
void		bitmask_add(t_bitmask *src, t_bitmask *dst);
void		bitmask_remove(t_bitmask *src, t_bitmask *dst);
int			bitmasks_are_equal(t_bitmask *left, t_bitmask *right);
int			bitmasks_share_bits(t_bitmask *left, t_bitmask *right);

/* ERROR MANAGEMENT*/
int			error_center(t_info *info, int error_code, t_hasht *table);

/* STORAGE */
t_path		*get_path_arr(void);
t_pathgroup	*get_groups_arr(void);
t_queue		*get_queue(void);
t_flowmap	*get_working_flowmap(void);
t_flowmap	*get_stable_flowmap(void);

#endif
