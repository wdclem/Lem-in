/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_o.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccariou <ccariou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 11:02:59 by ccariou           #+#    #+#             */
/*   Updated: 2022/09/09 11:56:17 by ccariou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/../includes/ft_printf.h"

static unsigned long long	change_size(t_info *info, unsigned long long i)
{
	if ((ft_strcmp(info->size, "ll")) == 0)
		return (i = va_arg(info->list, unsigned long long));
	else if ((ft_strcmp(info->size, "l")) == 0)
		return (i = va_arg(info->list, unsigned long));
	else if ((ft_strcmp(info->size, "h")) == 0)
		return (i = (unsigned short int)va_arg(info->list, unsigned int));
	else if ((ft_strcmp(info->size, "hh")) == 0)
		return (i = (unsigned char)va_arg(info->list, unsigned int));
	else
		return (va_arg(info->list, unsigned int));
}

static void	more_edge(t_info *info, int len)
{
	if (len > 0 && info->precision != 0)
	{
		ft_strdel(&info->mod);
		info->mod = ft_strnew(len);
		if (info->mod == NULL)
			return ;
		ft_memset(info->mod, '0', len);
	}
	else
	{
		ft_strdel(&info->mod);
		info->mod = ft_strnew(1);
		if (info->mod == NULL)
			return ;
		if (len == 0 && info->precision != 0 && info->copy[0] != '0')
		{
			ft_strdel(&info->mod);
			len = 1;
			info->mod = ft_strnew(1);
			if (info->mod == NULL)
				return ;
			ft_memset(info->mod, '0', len);
		}
	}
}

static void	hash_flag(t_info *info, int limit)
{
	char				*temp;

	temp = NULL;
	limit = ft_strlen(info->mod) + info->copylen;
	if (limit <= info->precision)
		return ;
	else
	{
		temp = ft_strjoin(info->mod, temp);
		if (temp == NULL)
			return ;
		ft_strdel(&(info->mod));
		info->mod = ft_strjoin("0", info->mod);
		if (info->mod == NULL)
			return ;
		ft_strdel(&temp);
	}
}

int	type_o(t_info *info)
{
	unsigned long long	i;
	int					len;
	int					limit;

	i = 0;
	i = change_size(info, i);
	if (!edge_case(info, i))
		convert(info, i, 8);
	len = info->precision - info->copylen;
	more_edge(info, len);
	limit = len + info->copylen;
	if (ft_strchr(info->flag, '#')
		&& limit <= info->precision && info->copy[0] != '0')
		hash_flag(info, limit);
	return (0);
}
