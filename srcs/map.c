/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccariou <ccariou@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 15:15:13 by ccariou           #+#    #+#             */
/*   Updated: 2022/11/08 13:46:04 by ccariou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

/*
 * Logic is to check if the line have the needed requirements.
 * They can all have comment and command, first one should be only number
 * room should have space between numbers
 * link should be - with numbers
 * nothing after
 * can probably make a isnum function for the numbers
 */

int	validate_map(t_info *info)
{
	int		i;

	i = 0;
	while (info->str[i][0] == '#' || (info->str[i] >= '0' && info->str[i] <= '9'))
	{
		valid_ants(info);
		i++;
	}
	while (info->str[i][0] == '#' || ft_strchr(info->str[i], ' '))
	{
		i = valid_room(info);
		info->room += 1;
		i++;
	}
	while (info->str[i][0] == '#' || ft_strchr(info-str[i], '-'))
	{
		i = valid_link(info, i);
		info->link += 1;
		i++;
	}
	if (input[i])
		return (1); // AKA ERROR SHould not have anything after the links 
	else
		return (0);
}


int	save_map(t_info *info)
{
	char	*line
	int		i;
	int 	len;
	int 	gnl_ret;

	line = NULL;
	i = 0;
	len = 5000;// Find a smarter way to put no limit to the file, dynamic ?
	gnl_ret = 1;
	info->str = (char **)malloc(sizeof(char *) * len + 1);
	if (!str)
		return(ERROR_MALLOC);
	while(gnl_ret)
	{
		gnl_ret = get_next_line(0, &line);
		if (gnl_ret == 0)
			break;
		if (gnl_ret < 0)
			return(ERROR_GNL);
		info->str[i] = line;
		i++;
		free(&line);
	}
	if (line)
		free(&line);
	return (0);
}
/*
int	valid_map(t_info *info)
{
	int	i;

	i = 0;
	while(info->str[i])
	{
		while((info->str[i][0] < '0' && info->str[i][0] > '9') || info->str[i][0] == '#')
			i++;
		while(ft_strchr(info->str[i], ' ') || info->str[i][0] == '#')
		{
			info->room += 1;
			i++;
		}
		while(ft_strchr(info->str[i], '-') || info->str[i][0] == '#')
		{
			info->link += 1;
			i++;
		}
		if (info->str[i] != NULL)
		{
			error_hub(info);
			return (1);
	}
	*/

