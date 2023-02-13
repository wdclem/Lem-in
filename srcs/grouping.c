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

void		grouping_add_path_to_group(t_pathgroup *group, t_path *path)
{
	ft_printf("adding path id:%d len:%d to group:%dp:%p\n", path->id, path->len, group->id, group);
	group->arr[group->len] = path;
	group->total_path_len += path->len;
	group->len++;
}
