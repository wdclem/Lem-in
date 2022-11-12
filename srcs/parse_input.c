/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccariou <ccariou@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 11:50:00 by ccariou           #+#    #+#             */
/*   Updated: 2022/10/26 17:23:40 by ccariou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int	is_command(t_info *info, int i)
{
	if(strcmp(info->str[i], "##start") == 0)
	{
		info->start = i;
		return (1);
	}
	else if(strcmp(info->str[i], "##end") == 0)
	{
		info->end= i;
		return(1);
	}
	else
		return(0);
}

/*
 * Validate rooms and saves it if input is valid
 */

int	validate_rooms(t_info *info, int i;)
{
	while (strchr(info->str[i], ' ')) 
	{
		if (!info->str && info->str[i][0] != 'L')
			return (error_hub(ROOM_ERROR));
		if (!info->start == 0 && info->end == 0)
		

}

/*
 * Validate ants and saves it if input is valid
 */

int	validate_ants(t_info *info, int i)
{
	if (!is_command)
		i++;
	info->ants = ft_atoi(info->str[i]);
	if (!info->ants || info->ants < 0 || info->ants > MAX_ANTS
			|| !ft_isdigit(info->ants))
		return (error_hub(ANTS_INPUT_ERROR));
	return (i);
}

int	check_save(t_info *info, int i)
{
	i = validate_ants(info, i);
	i = validate_rooms(info, i);
	i = validate_links(info, i);
	return (0);
}

