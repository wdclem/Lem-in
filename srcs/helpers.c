/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccariou <ccariou@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 13:33:00 by ccariou           #+#    #+#             */
/*   Updated: 2023/02/15 17:53:57 by ccariou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int	dj2b_hash(char *key)
{
	int				i;
	unsigned long	hash;

	i = 0;
	hash = 5381;
	while (key[i] != '\0')
	{
		hash = (((hash << 5) + hash) + key[i]) % HT_CAP;
		i++;
	}
	return (hash);
}

int	valid_amount_of_spaces_in_room_name(t_info *info, int i)
{
	int	idx;
	int	space_count;

	idx = 0;
	space_count = 0;
	while (info->str[i][idx])
	{
		space_count += ft_isspace(info->str[i][idx]);
		idx++;
	}
	if (space_count != 2)
		return (ERROR);
	return (1);
}

static void	set_start_end(t_info *info, t_hasht *table, int i)
{
	if (info->s_check == 1 && !info->start)
		info->start = table->room[i];
	else if (info->e_check == 1 && !info->end)
		info->end = table->room[i];
}

int	set_table(t_info *info, t_hasht *table, char *room_key)
{
	int		i;

	i = dj2b_hash(room_key);
	while (table->room[i])
	{
		if (unique_id(i, table, room_key) != 0)
			return (ERROR);
		i++;
		if (i >= HT_CAP)
			i = 0;
	}
	table->room[i] = make_room(info, room_key);
	if (table->room[i] == NULL)
		return (ERROR);
	if (!info->start || !info->end)
		set_start_end(info, table, i);
	return (0);
}

int	check_comment_for_start_and_end(t_info *info, int i)
{
	int	ret;

	ret = 0;
	info->s_check = ft_strequ(info->str[i], "##start");
	info->e_check = ft_strequ(info->str[i], "##end");
	if (info->s_check || info->e_check)
	{
		if ((info->str[i + 1] && info->str[i + 1][0] == '#'))
			return (-1);
		else if (info->str[i + 1] && info->str[i + 1][0] == 0)
			return (-1);
		ret = 1;
	}
	return (ret);
}
