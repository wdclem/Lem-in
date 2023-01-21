/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_s.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccariou <ccariou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 11:00:24 by ccariou           #+#    #+#             */
/*   Updated: 2022/09/09 11:56:17 by ccariou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/../includes/ft_printf.h"

static void	more_edge(t_info *info, char *str)
{
	if (str)
	{
		info->copy = ft_strnew(info->copylen + 1);
		if (info->copy == NULL)
			return ;
		ft_strcpy(info->copy, str);
	}
	else
	{
		info->copy = ft_strnew(6);
		if (info->copy == NULL)
			return ;
		info->copylen = 6;
		ft_strcpy(info->copy, "(null)");
	}
	if (info->precision > 0 && info->precision < info->copylen)
	{
		info->copy[info->precision] = '\0';
		info->copylen = ft_strlen(info->copy);
	}
}

int	type_str(t_info *info)
{
	char	*str;

	if (info->precision == 0)
	{
		info->copy = ft_strnew(1);
		if (info->copy == NULL)
			return (1);
		ft_strcpy(info->copy, "\0");
		return (1);
	}
	str = va_arg(info->list, char *);
	info->copylen = ft_strlen(str);
	more_edge(info, str);
	return (0);
}
