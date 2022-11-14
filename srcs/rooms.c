/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rooms.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccariou <ccariou@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 11:34:27 by ccariou           #+#    #+#             */
/*   Updated: 2022/11/14 17:11:26 by ccariou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static void	save_room(t_info *info, t_room *rooms)
{
	while(info->str[i] == ' ' )
	{
		room->id[i] = info->str[i][0];
		i++;
	}
}

void	validate_room_input(char **room_checker)
{
	int	i;

	i = 0;
	while(room_checker[i] != NULL)
		i++;
}

int	validate_room(t_info *info, int i)
{
	char	**room_checker;
	//Check if room is valid
	while(info->str)
	{
		if (ft_strchr(info->str[i], "L"))
			return(ERROR);
		if (ft_strchr(info->str[i], "#"))
			return (0);
		else if (ft_strchr(info->str[i], ' ')) 
		{
			room_checker = ft_strsplit(info->str[i], ' ')
			if (valid_room_input(room_checker) != 3)
				return(ERROR);
		}
		/* char **valid_room;
		 * valid_room = ft_split(info->str[i]) if more than 3 split ERROR, if no 0 1 2 ERROR if 0 isnot alphanum and if 1 2 arenet digit ERROR else valid
		 */
			return (1);
	}
}

int	save_rooms(t_info info)
{
	int	i;

	i = 1;
	start_check = 0;
	while(info->str && strchr(info->str[i], ' '))
	{
		if (ft_strchr(info->str[i], "##start"))
			info->start = 1;
		else if (ft_strchr(info->str[i], "##end"))
			info->end = 1;
		if (ft_strchr(info->str[i], ' '))
		{
			if(valid_room(info, i) == 1)
			{
				save_room(info, room);
				info->rooms += 1;
		}
		i++;
	}
	if (!info->start > 0 && !info->end == 1)
		return(ERROR);
	return (i);
}


