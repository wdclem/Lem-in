/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   links.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccariou <ccariou@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 15:19:43 by ccariou           #+#    #+#             */
/*   Updated: 2023/02/15 19:42:24 by ccariou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static int	add_link(t_room *from, t_room *link_to)
{
	t_link	*link;

	link = from->link_head;
	if (link != NULL)
	{
		while (link->next != NULL)
			link = link->next;
		link->next = new_link(from, link_to);
	}
	else
		from->link_head = new_link(from, link_to);
	return (0);
}

t_room	*pointer_to_room(t_hasht *table, char *id)
{
	t_room	*room;
	int		j;

	j = 0;
	if (!id)
		return (NULL);
	j = dj2b_hash(id);
	while (ft_strcmp(table->room[j]->id, id) != 0)
	{
		j++;
		if (j >= HT_CAP)
			j = 0;
	}
	room = table->room[j];
	if (room == NULL)
		return (NULL);
	room->link_count += 1;
	return (room);
}

static int	check_link_amount(char **link, int *count)
{
	*count = 0;
	while (link[*count])
		(*count)++;
	if ((*count) != 2 || ft_strcmp(link[0], link[1]) == 0)
		return (ERROR);
	return (0);
}

static int	check_link(t_info *info, t_hasht *table, int i)
{
	char	**link;
	int		count;
	t_room	*from;
	t_room	*link_to;

	link = ft_strsplit(info->str[i], '-');
	if (!link)
		return (ERROR);
	if (check_link_amount(link, &count) == -1)
		return (free_str_split(link, count, ERROR));
	if (link_room_exist(table, link[0], link[1]) == -1)
		return (free_str_split(link, count, ERROR));
	if (link[0] && link[1])
	{
		from = pointer_to_room(table, link[0]);
		link_to = pointer_to_room(table, link[1]);
		if (!from || !link_to)
			return (free_str_split(link, count, ERROR));
		add_link(from, link_to);
		add_link(link_to, from);
	}
	ft_freearray((void ***)&link, count);
	return (0);
}

int	save_links(t_info *info, t_hasht *table, int i)
{
	while (i < info->total_strs && info->str[i])
	{
		ft_printf("str == %s\n", info->str[i]);
		if (ft_strchr(info->str[i], '-') && info->str[i][0] == '#' && \
			info->str[i][1] != '#')
			i++;
		if (info->str[i][0] == 0 || (!ft_strchr(info->str[i], '-') && \
			info->str[i][0] != '#') || (info->str[i][0] != '#' && \
			ft_strchr(info->str[i], '#')))
			return (ERROR);
		if (info->str[i][0] == '#')
		{
			if (check_comment_for_start_and_end(info, i) == -1)
				return (ERROR);
		}
		else if (ft_strchr(info->str[i], '-'))
		{
			if (!check_link(info, table, i))
				info->total_links += 2;
			else
				return (ERROR);
		}
		i++;
	}
	return (0);
}
