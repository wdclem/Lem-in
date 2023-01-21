/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_info.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccariou <ccariou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 13:13:44 by ccariou           #+#    #+#             */
/*   Updated: 2022/09/09 11:56:15 by ccariou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/../includes/ft_printf.h"

void	set_struc(t_info *info)
{
	info->copy = NULL;
	info->mod = NULL;
	info->minus_mod = NULL;
	info->isneg = 0;
	info->copylen = 0;
	info->modlen = 0;
	ft_memset (info->flag, 0, sizeof (info->flag));
	info->type = '0';
	info->width = 0;
	info->precision = -6;
	ft_memset (info->size, 0, sizeof (info->size));
	info->isneg = 0;
	info->cnull = 0;
	info->minuslen = 0;
}

void	print(t_info *info)
{
	if (info->type != 'c')
		info->copylen = ft_strlen(info->copy);
	info->modlen = ft_strlen(info->mod);
	ft_putstr(info->mod);
	if (info->cnull == 1)
		write(1, "\0", 1);
	else
		ft_putstr(info->copy);
	ft_putstr(info->minus_mod);
}

void	clean_up(t_info *info)
{
	ft_strdel(&info->mod);
	ft_strdel(&info->copy);
	ft_strdel(&info->minus_mod);
}

void	get_info(const char **ptr, t_info *info)
{
	check_flag(ptr, info);
	check_width(ptr, info);
	check_precision(ptr, info);
	check_size(ptr, info);
	check_conv(ptr, info);
}

void	dispatch(t_info *info, t_conv **type, int select)
{
	if (info->type == 'c')
		select = 0;
	else if (info->type == 's')
		select = 1;
	else if (info->type == 'p')
		select = 2;
	else if (info->type == 'd' || info->type == 'i')
		select = 4;
	else if (info->type == 'o')
		select = 5;
	else if (info->type == 'u')
		select = 6;
	else if (info->type == 'x')
		select = 7;
	else if (info->type == 'X')
		select = 8;
	else if (info->type == 'f')
		select = 9;
	else if (info->type == '%')
		select = 10;
	else
		return ;
	type[select](info);
}
