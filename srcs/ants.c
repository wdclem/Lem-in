/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ants.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccariou <ccariou@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 12:43:53 by ccariou           #+#    #+#             */
/*   Updated: 2022/11/09 11:01:17 by ccariou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	valid_ant(t_info *info)
{
	int	i;

	i = 0;
	if (info->str && ft_isdigit(info->str[0]))
	{
		while(info->str[i][0] == '#')
			i++;
		info->ants = ft_atoi(info->str[0]);
	}
	if (info->ants > 0 && info->ants < MAX_ANTS)
		return (1);
	else
		return(ERROR_INPUT);
	return (0);
}

/*
int	valid_rooms(t_info *info)
{
	
}

int	valid_links(t_info *info)
{}

int	check_valid(t_info *info)
{
	if (valid_map(info) == 1)
		error_hub(info);
	if (valid_ant(info) == 1)
		error_hub(info);
	if (valid_rooms(info) == 1)
		error_hub(info);
	if (valid_links(info) == 1)
		error_hub(info);
	return (0);
}*/
