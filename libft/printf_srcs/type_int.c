/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_int.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccariou <ccariou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 11:03:17 by ccariou           #+#    #+#             */
/*   Updated: 2022/09/09 11:56:16 by ccariou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/../includes/ft_printf.h"

static long long	change_size(t_info *info, long long i)
{
	if ((ft_strcmp(info->size, "ll")) == 0)
		return (i = va_arg(info->list, long long));
	else if ((ft_strcmp(info->size, "l")) == 0)
		return (i = va_arg(info->list, long));
	else if ((ft_strcmp(info->size, "h")) == 0)
		return (i = (signed short int)va_arg(info->list, int));
	else if ((ft_strcmp(info->size, "hh")) == 0)
		return (i = (signed char)va_arg(info->list, int));
	else
		return (va_arg(info->list, int));
}

static void	more_edge(t_info *info, int len)
{
	if (info->isneg == 1)
	{
		ft_memset(info->mod, '0', len + 1);
		info->mod[0] = '-';
		info->mod[len] = '\0';
	}
	else if (ft_strchr(info->flag, '+'))
	{
		ft_memset(info->mod, '0', len + 1);
		info->mod[0] = '+';
		info->mod[len] = '\0';
	}
	else if (ft_strchr(info->flag, ' '))
	{
		ft_memset(info->mod, '0', len + 1);
		info->mod[0] = ' ';
		info->mod[len] = '\0';
	}
	else
		info->mod[len - 1] = '\0';
}

static void	add_flag(t_info *info)
{
	int	len;

	len = info->precision - info->copylen + 1;
	if (len <= 0)
		len = 1;
	info->mod = ft_strnew(len);
	if (info->mod == NULL)
		return ;
	ft_memset(info->mod, '0', len);
	more_edge(info, len);
}

int	type_int(t_info *info)
{
	long long	i;

	i = 0;
	i = change_size(info, i);
	if (!edge_case(info, i))
	{
		if (i < -9223372036854775807)
		{
			if (i < 0)
			{
				info->isneg = 1;
				convert(info, i, 10);
			}
		}
		else if (i < 0)
		{
			i *= -1;
			info->isneg = 1;
			signed_numb(info, i, 10);
		}
		else
			signed_numb(info, i, 10);
	}
	add_flag(info);
	return (0);
}
