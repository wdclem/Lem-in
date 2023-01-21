/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_f.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccariou <ccariou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 14:53:11 by ccariou           #+#    #+#             */
/*   Updated: 2022/10/03 11:26:12 by ccariou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/../includes/ft_printf.h"

static long double	round(long double num, int precision)
{
	long double	extra;
	int			i;
	int			helper;

	i = precision;
	extra = 0.5;
	while (precision-- > 0)
	{
		num -= (long)num;
		num *= 10;
	}
	helper = (int)num;
	num -= (int)num;
	while (i-- > 0)
		extra /= 10;
	if (num == 0.5 && (num - num == 0.0) && helper % 2 == 0)
		extra = 0.0;
	return (extra);
}

static void	join(t_info *info, char *str)
{
	char	*temp;

	temp = NULL;
	temp = ft_strjoin(info->copy, temp);
	if (temp == NULL)
		return ;
	ft_strdel(&info->copy);
	info->copy = ft_strjoin(temp, str);
	if (info ->copy == NULL)
		return ;
	ft_strdel(&str);
	ft_strdel(&temp);
}

static void	fractional_part(t_info *info, long double after_dot)
{
	char			*str;
	unsigned int	i;

	if (info->precision == 0 && ft_strstr(info->flag, "#"))
	{
		info->copy = ft_strjoin(info->copy, ".");
		if (info->copy == NULL)
			return ;
		return ;
	}
	else if (!info->precision)
		return ;
	i = info->precision;
	str = ft_strnew(i + 1);
	if (str == NULL)
		return ;
	str[0] = '.';
	while (i > 0)
	{
		after_dot *= 10.0;
		str[info->precision + 1 - i] = ((int)after_dot % 10) + '0';
		i--;
		after_dot -= (int)(after_dot);
	}
	join(info, str);
}

static void	build_float(t_info *info, long double numb)
{
	long		before_dot;
	long double	after_dot;

	if (info->precision < 0)
		info->precision = 6;
	numb += round(numb, info->precision);
	before_dot = (long)numb;
	after_dot = numb - (long double)before_dot;
	signed_numb(info, before_dot, 10);
	fractional_part(info, after_dot);
	info->copylen = ft_strlen(info->copy);
	if (info->isneg || info->flag[0])
	{
		info->mod = ft_strnew(1);
		if (info->mod == NULL)
			return ;
		if (info->isneg == 1)
			info->mod[0] = '-';
		else if (ft_strchr(info->flag, '+'))
			info->mod[0] = '+';
		else if (ft_strchr(info->flag, ' '))
			info->mod[0] = ' ';
	}
}

int	type_f(t_info *info)
{
	long double	i;

	i = 0;
	if ((ft_strcmp(info->size, "L")) == 0)
		i = va_arg(info->list, long double);
	else
		i = va_arg(info->list, double);
	if (i < 0.0 || (i == -0.0 && 1.0 / i != 1 / 0.0))
	{
		info->isneg = 1;
		i *= -1;
	}
	build_float(info, i);
	return (0);
}
