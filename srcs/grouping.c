/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grouping.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccariou <ccariou@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 16:47:35 by ccariou           #+#    #+#             */
/*   Updated: 2023/02/09 12:03:25 by ccariou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int	grouping_score_group(t_info *info, t_pathgroup *group)
{
	double		turns;

	if (group->len == 0)
		return (MAX_ROOMS + 2);
	turns = 0;
	turns = (group->total_path_len + info->ants) / group->len;
	if (turns - (int)turns != 0)
		turns += 1;
	return (turns);
}

void	grouping_add_path_to_group(t_info *info, t_pathgroup *group, \
		t_path *path)
{
	bitmask_clear_idx(&path->rooms_used, info->end->number);
	bitmask_add(&path->rooms_used, &group->rooms_used);
	group->arr[group->len] = path;
	group->total_path_len += path->len;
	group->len++;
}

static t_path	*find_optimized_path(t_queue *queue, t_info *info, \
		t_path *current_path, t_pathgroup *group)
{
	t_queueitem	*item;
	t_link		*link;
	int			i;

	i = 0;
	while (i < queue->top && i < current_path->len)
	{
		item = &queue->arr[i++];
		link = item->room->link_head;
		while (link != NULL)
		{
			if (link->link_to == info->start)
				return (path_make_next(info, item));
			if (!bitmask_check_idx(&queue->rooms_used, link->link_to->number)
				&& !bitmask_check_idx(&group->rooms_used, \
				link->link_to->number) && link->link_to->distance <= \
				item->room->distance)
				queue_add_item(&queue, link->link_to, link, item);
			link = link->next;
		}
	}
	return (NULL);
}

void	grouping_optimize_pathgroup(t_queue *queue, t_info *info, \
		t_pathgroup *group)
{
	t_path		*next_path;
	t_path		*new_path;
	int			path_idx;

	path_idx = 0;
	while (path_idx < group->len)
	{
		next_path = group->arr[path_idx];
		bitmask_remove(&next_path->rooms_used, &group->rooms_used);
		queue_clear(&queue);
		queue_add_item(&queue, info->end, NULL, NULL);
		new_path = find_optimized_path(queue, info, next_path, group);
		if (new_path && new_path->len < next_path->len)
		{
			group->arr[path_idx] = new_path;
			bitmask_add(&new_path->rooms_used, &group->rooms_used);
		}
		else
			bitmask_add(&next_path->rooms_used, &group->rooms_used);
		path_idx++;
	}
}
