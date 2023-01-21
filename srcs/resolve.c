/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolve.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccariou <ccariou@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 12:29:11 by ccariou           #+#    #+#             */
/*   Updated: 2023/01/11 12:56:04 by ccariou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"
/* 
 * if curr_turn becomes bigger than min_turn,
 * then we found the shortest path set so return TRUE
 */
int	get_result_condition(t_info *info, t_result *result,
							t_path *path_curr, int *count)
{
	static int	keep;

	if (*count == 1)
		result->tmp_head = path_curr;
	if (update_link_weight(info, path_curr))
	{
		init_unused_links(info, result->tmp_head);
		*count = 0;
	}
	else
	{
		count_turn(info, result, *count);
		if (*count == 1)
			keep = result->curr_turn;
		else
		{
			if (keep < result->curr_turn)
				return (TRUE);
			keep = result->curr_turn;
		}
	}
	return (FALSE);
}

int	get_result(t_info *info, t_result *result)
{
	t_path	*curr;
	t_path	*next_path;
	int		count;

	count = 1;
	path_curr = NULL;
	if (bfs(info, &path_curr, TRUE) == FALSE || path_curr == NULL)
		return (FALSE);
	result->path_head = path_curr;
	result->curr_turn = 0;
	result->tmp_head = path_curr;
	count_turn(info, result, count);
	while (path_curr)
	{
		if (get_result_condition(info, result, path_curr, &count))
			break ;
		path_next = NULL;
		if (bfs(info, &path_next, TRUE) == FALSE)
			return (FALSE);
		path_curr->next = path_next;
		path_curr = path_next;
		count++;
	}
	return (TRUE);
}

int	solve(t_info *info)
{
	t_result	result;

	if (get_result(info) != 0)
		return(ERROR);
// TODO free
	return (0);
}
