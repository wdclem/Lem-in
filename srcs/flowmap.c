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

int			flow_allows_room_movement(t_flowmap *flowmap, t_room *room)
{
	int		free_links;
	int		link_taken;
	t_link	*current_link;

	free_links = room->link_count;
	link_taken = 0;
	current_link = room->link_head;
	while (current_link != NULL)
	{
		link_taken |= bitmask_check_idx(&flowmap->upstream,
				current_link->number);
		link_taken |= bitmask_check_idx(&flowmap->blocked,
				current_link->number);
		if (!link_taken)
			bitmask_set_idx(&flowmap->open, current_link->number);
		free_links -= link_taken;
	}
	return (free_links);
}

