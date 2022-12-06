/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rooms.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccariou <ccariou@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 11:34:27 by ccariou           #+#    #+#             */
/*   Updated: 2022/12/06 14:07:36 by ccariou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static int	save_room(t_info *info, t_room *room, int i)
{
	int		j;

	j = 0;
//	printf("save room i = %d\n", i);
//	printf("info->roos == %d\n", info->rooms);
	if(!ft_strchr(info->str[i], '-'))
	{
		printf("j  = %d\n", j);
		while(room->id[j] != '\0')
			j++;
		i = check_comment(info, i);
		room->id[j] = info->str[i][0];
		/*
		printf("info->str[i] == %s\n", info->str[i]);
		printf("room = %d i = %d j = %d\n", room->id[j], i,  j);
		*/
	}
	printf("before return i = %d\n", i);
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

int	validate_room(t_info *info, t_room *room, int i)
{
	char	**room_checker;

	if (ft_strchr(info->str[i], ' ')) 
	{
		room_checker = ft_strsplit(info->str[i], ' ');
		if (validate_room_input(room_checker) != 3)
			return(ERROR);
		if(ft_atoi(room_checker[1]) < 0 || ft_atoi(room_checker[2]) < 0)
			return(ERROR);
		if (!unique_id(room, room_checker))
			return(ERROR);
	}
		/* char **valid_room;
		 * valid_room = ft_split(info->str[i]) if more than 3 split ERROR, if no 0 1 2 ERROR if 0 isnot alphanum and if 1 2 arenet digit ERROR else valid
		 */
	//}
	return (1);
}

int	save_rooms(t_info *info, t_room *room, int i)
{
//	int	start_check;

//	start_check = 0;
	printf("initial i in save_room == %d\n", i);
	while(info->str[i] != NULL)
	{
		i = check_comment(info, i);
		if (ft_strchr(info->str[i], 'L'))
			return(ERROR);
		if (ft_strchr(info->str[i], ' '))
		{
			printf("info->str[i] == %s\n", info->str[i]);
			if(validate_room(info, room, i) == 1)
			{
				i = save_room(info, room, i);
				info->rooms += 1;
			}
		}
		printf("after loop i = %d\n", i);
		i++;
	}
	printf("info->rooms == %d\n", info->rooms);
	if (info->start < 0 && info->end != 1)
		return(ERROR);
	return (i);
}


