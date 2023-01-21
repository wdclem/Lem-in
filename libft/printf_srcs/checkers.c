/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccariou <ccariou@hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 10:42:00 by ccariou           #+#    #+#             */
/*   Updated: 2022/09/09 11:56:13 by ccariou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/../includes/ft_printf.h" 

int	check_flag(const char **ptr, t_info *info)
{
	int	i;

	++*ptr;
	i = 0;
	while (**ptr && ft_strchr(" #0-+", **ptr))
	{
		info->flag[i] = **ptr;
		++*ptr;
		i++;
	}
	return (0);
}

void	check_width(const char **ptr, t_info *info)
{
	long long	numblen;

	while (ft_isspace(**ptr))
		ptr++;
	if (**ptr == '*')
	{
		info->width = va_arg(info->list, int);
		if (info->width < 0)
		{
			info->width *= -1;
			ft_strcat(info->flag, "-");
		}
		++*ptr;
	}
	if (ft_isdigit(**ptr))
	{
		info->width = ft_atoi(*ptr);
		numblen = 0;
		numblen = numb_len(numblen, 10);
		if (info->width <= 9)
			++*ptr;
		else
			while (numblen-- > -1)
				++*ptr;
	}
}

int	check_precision(const char **ptr, t_info *info)
{
	if (**ptr != '.')
		return (0);
	++*ptr;
	info->precision = 0;
	if (ft_isdigit(**ptr))
	{
		info->precision = ft_atoi(*ptr);
	}
	else if (**ptr == '*')
	{
		info->precision = va_arg(info->list, int);
		if (info->precision < 0)
			info->precision = -1;
		++*ptr;
		return (0);
	}
	else
		return (1);
	while (ft_isdigit(**ptr))
		++*ptr;
	return (0);
}

int	check_size(const char **ptr, t_info *info)
{
	int	i;

	i = 0;
	while (**ptr && ft_strchr("Llh", **ptr))
	{
		info->size[i] = **ptr;
		++*ptr;
		i++;
	}
	return (0);
}

int	check_conv(const char **ptr, t_info *info)
{
	int	i;

	i = 0;
	if (**ptr && ft_strchr("cspdiouxXf%", *ptr[i]))
		info->type = *ptr[i];
	else
		return (1);
	return (0);
}
