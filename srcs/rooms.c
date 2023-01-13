/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rooms.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccariou <ccariou@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 11:34:27 by ccariou           #+#    #+#             */
/*   Updated: 2023/01/05 21:55:11 by ccariou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"


/* Create a new room in the HT
 * TODO check if coordinate needed/ t_coord ?
 */
static int	set_table(t_info *info, t_hasht *table, char *room_key, int x, int y)
{
	int		i;
//	t_room	*prev_room;
	t_room	*new_room;

	i = dj2b_hash(room_key);
	new_room = table->room[i];
//	prev_room = NULL; 
	if (!new_room)
	{
		table->room[i] = make_room(room_key, x, y);
		printf("room[%d] == %s\n", i, table->room[i]->id);
//		printf("room[%d] == %s\n", i, table->room[i]->id);
	}
	if (info->s_check == 1)
	{
		info->start= table->room[i];
//		printf("start room[%d] == %s\n", i, info->start->id);
		//info->start = new_room;
		info->s_check = 0;
	}
	else if (info->e_check == 1)
	{
		info->end = table->room[i];
//		printf("teub\n");
//		info->end = new_room;
//		printf("end room[%d] == %s\n", i, info->end->id);
		info->e_check = 0;
	}
	while (new_room != NULL)
	{
		if (!ft_strequ(room_key, new_room->id))
			return (ERROR);
	}
//	prev_room->next = make_room(room_key, x, y);
	return(0);
}

static int	room_to_hasht(t_info *info, t_hasht *table, int i, char **room_checker)
{
	int		j;

	j = -1;
//	printf("room checker == %s\n", room_checker[0]);
	set_table(info, table, room_checker[0], ft_atoi(room_checker[1]), ft_atoi(room_checker[2]));
/*	if (info->start == i)
		info->s_room= get(ht, arr[0]);
	else if (info->end == i)
		info->e_room= get(ht, arr[0]);
	*/
	while (room_checker[++j])
		free(room_checker[j]);
	free(room_checker);
	return (ERROR);
	/*
	if(!ft_strchr(info->str[i], '-'))
	{
		printf("j  = %d\n", j);
		while(room->id[j] != '\0')
			j++;
		i = check_comment(info, i);
		room->id[j] = info->str[i][0];
		printf("info->str[i] == %s\n", info->str[i]);
		printf("room = %d i = %d j = %d\n", room->id[j], i,  j);
	}
	*/
//	printf("before return i = %d\n", i);
	return (i);
}

int	validate_room_input(char **room_checker)
{
	int	split;

	split = 0;
	while(room_checker[split] != NULL)
		split++;
	return (split);
}

int	unique_id(t_room *room, char **room_checker)
{
	int	i;
	
	i = 0;
	while(room->id[i])
	{
		if (!ft_strcmp(room->id, room_checker[0]))
			return (1);
		i++;
	}
	return (0);
}

int	validate_room(t_info *info, t_hasht *table, int i)
{
	char	**room_checker;

	room_checker = ft_strsplit(info->str[i], ' ');
	if (validate_room_input(room_checker) != 3)
		return(ERROR);
	if(ft_atoi(room_checker[1]) < 0 || ft_atoi(room_checker[2]) < 0)
		return(ERROR);
	else	
		room_to_hasht(info, table, i, room_checker);
	return (1);
}

int	save_rooms(t_info *info, t_hasht *table, int i)
{
//	int	start_check;

//	start_check = 0;
	printf("*********ROOMS********\n");
	while (info->str[i] && !ft_strchr(info->str[i], '-'))
	{
		if (ft_strchr(info->str[i], 'L'))
			return(ERROR);
		else if (info->str[i][0] == '#')
			i = check_comment(info, i);
		if (ft_strchr(info->str[i], ' '))
		{
//			printf("info->str[i] == %s\n", info->str[i]);
			if(validate_room(info, table, i) == 1)
				info->rooms += 1;
		}
		printf("after loop i = %d\n", i);
		i++;
	}
//	printf("info->rooms == %d\n", info->rooms);
	if (!info->start && !info->end)
		return(ERROR);
	return (i);
}


