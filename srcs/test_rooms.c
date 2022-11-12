/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rooms.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccariou <ccariou@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 17:06:55 by ccariou           #+#    #+#             */
/*   Updated: 2022/10/24 18:41:29 by ccariou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	save_room(t_info *info)
{




int	valid_room(t_info *info, char *line)
{
	//Check if room is valid
	if (*line == 'L')
		return(ERROR);
	if (*line == '#')
		hash_checker(line);
	else if ((*line >= '0' && *line <= '9') && ft_strchr(*line, ' '))
		save_room;
}

int	parse_room(t_info *info)
{
	char	*line;
	int		ret;

	line = NULL;
	ret = 0;
	while(info->line)
	{
		ret = get_next_line(0, &line);
		if (ret == 0)
			break;
		if (ret < 0)
			return(ERROR_GNL);
		valid_room;
		save_room;
		free(line);
	}
	return (0);
}
		
