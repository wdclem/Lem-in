/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flowmap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccariou <ccariou@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 16:47:35 by ccariou           #+#    #+#             */
/*   Updated: 2023/02/07 12:22:25 by ccariou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static inline const char *flow_to_str(t_flowmask flow)
{
	const char	*strs[] = {
		"Open",
		"A to B",
		"B to A",
		"",
		"Blocked"
	};

	return (strs[(int)flow]);
}

static inline void	flowmap_debug_print(t_flowmap *flowmap, int count)
{
	for (int i = 0; i < count; i++)
	{
		printf("Link %d: %s\n", i, flow_to_str(flowmap->arr[i]));
	}
}

void	flowmap_update_stable_map(t_flowmap *working, t_flowmap *stable, \
		int total_links)
{
	printf("Working flowmap at this point in time:\n");
		flowmap_debug_print(working, total_links);
	printf("Working flowmap at this point in time:\n");
	flowmap_debug_print(stable, total_links);
}
t_path	*flowmap_find_path(t_queue *queue, t_flowmap *flowmap, \
				t_info *info)
{
	(void)queue;
	(void)flowmap;
	t_flowmap *working_flowmap = get_working_flowmap();
	t_flowmap *stable_flowmap = get_stable_flowmap();
	printf("Working flowmap at this point in time:\n");
	flowmap_debug_print(working_flowmap, info->total_links);
	printf("Working flowmap at this point in time:\n");
	flowmap_debug_print(stable_flowmap, info->total_links);
	return (NULL);
}
