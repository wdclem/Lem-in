/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   links.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccariou <ccariou@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 15:19:43 by ccariou           #+#    #+#             */
/*   Updated: 2022/12/06 15:28:18 by ccariou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int	save_links(t_info *info)
{
	int		i;
	char	*link;

	while(info->str[i] == '-')
	{
		ft_split(info->str[i])
		if (room_current = link[0])
		{
			room->links[0] = link[1];
			link_count++;
		}
	}
	/*i
	0 1
	b c
	link_count++;
	*/
}

int	validate_links(t_info info, int	i)
{
	char	**link;
	
	link = NULL;
	while (info->str[i] && (ft_strchr(info->str[i], '-') || info->str[i][0] == '#'))
	{
		if (info->str[i][0] != '#' && ft_strchr(info->str[i], '-'))
		{
			link = ft_strsplit(info->str[i], '-');
			if (!ft_isdigit(link[0]) && !ft_isdigit(link[1])) /* check if they are digit aswell */
				return(ERROR);
			else
				i++;
		}
	}
	IF VALID
		SAVE LINKS
	return (i);
}



room = 0 2 3 1 hello good
	0 - 2
	2 - 3
	3 - 1
	1 - hello
	hello - good

0 0	
1 2
2 3
4 1
5 hello
6 good

0 0 1
1 1 2
2 2 4
3 4 5
4 5 6
