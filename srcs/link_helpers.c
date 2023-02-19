/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   link_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccariou <ccariou@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 18:19:21 by ccariou           #+#    #+#             */
/*   Updated: 2023/02/15 18:56:29 by ccariou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static int	link_room_exists(t_hasht *table, char *room_name, int *hash)
{
	int	exist;

	if ((*hash) == HT_CAP)
		(*hash) = 0;
	exist = 0;
	if (ft_strcmp(table->room[(*hash)]->id, room_name) != 0)
	{
		(*hash)++;
		while (table->room[(*hash)] != NULL)
		{
			if (ft_strcmp(table->room[(*hash)]->id, room_name) == 0)
				return (0);
			(*hash)++;
			if ((*hash) == HT_CAP)
				(*hash) = 0;
		}
		exist = -1;
	}
	return (exist);
}

int	link_room_exist(t_hasht *table, char *from, char *link_to)
{
	int		hash_from;
	int		hash_to;
	int		exist;
	t_link	*next_link;

	exist = 0;
	if (!from || !link_to || !table)
		return (ERROR);
	hash_from = dj2b_hash(from);
	hash_to = dj2b_hash(link_to);
	if (!table->room[hash_from] || !table->room[hash_to])
		return (ERROR);
	exist = link_room_exists(table, from, &hash_from);
	exist = link_room_exists(table, link_to, &hash_to);
	if (exist == -1)
		return (ERROR);
	next_link = table->room[hash_from]->link_head;
	while (next_link)
	{
		if (ft_strcmp(next_link->link_to->id, link_to) == 0)
			return (ERROR);
		next_link = next_link->next;
	}
	return (0);
}
