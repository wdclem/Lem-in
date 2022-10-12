/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccariou <ccariou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 10:21:35 by ccariou           #+#    #+#             */
/*   Updated: 2022/09/09 11:56:15 by ccariou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/../includes/ft_printf.h"

/*
* cspdiouxXf% 
* %[flags][width][.precision][size]type
*/
static void	initialize_type(t_conv **type)
{
	type[0] = &type_c;
	type[1] = &type_str;
	type[2] = &type_p;
	type[3] = &type_int;
	type[4] = &type_int;
	type[5] = &type_o;
	type[6] = &type_unsigned;
	type[7] = &type_x;
	type[8] = &type_xcap;
	type[9] = &type_f;
	type[10] = &type_percent;
}

static int	minus_flag(t_info *info, char *temp, int len)
{
	if (ft_strchr(info->flag, '-'))
	{
		temp[len - info->modlen] = '\0';
		info->minus_mod = temp;
		return (0);
	}
	else
		return (1);
}

void	size_mod(t_info *info)
{
	int		len;
	char	*temp;
	int		position;

	info->modlen = ft_strlen(info->mod);
	len = info->width - info->copylen;
	if (len <= info->modlen)
		return ;
	temp = ft_strnew(len);
	if (temp == NULL)
		return ;
	ft_memset(temp, ' ', len);
	if (!minus_flag(info, temp, len))
		return ;
	if ((info->precision < 0 || !ft_strchr("diouxX", info->type))
		&& ft_strchr(info->flag, '0'))
		ft_memset(temp, '0', len);
	position = (len - info->modlen) * (temp[0] != '0');
	if (info->mod)
		ft_strncpy(&temp[position], info->mod, info->modlen);
	ft_strdel(&info->mod);
	info->mod = temp;
}

int	check_percentage(const char **ptr, t_info *info)
{
	t_conv	*type[11];
	int		select;

	select = 0;
	initialize_type(type);
	get_info(ptr, info);
	dispatch(info, type, select);
	size_mod(info);
	print(info);
	return (0);
}

int	ft_printf(const char *str, ...)
{
	t_info		info;

	va_start(info.list, str);
	set_struc(&info);
	info.charcount = 0;
	while (*str != '\0')
	{
		if (*str == '%')
		{
			check_percentage(&str, &info);
			info.charcount += (info.copylen + info.modlen
					+ (ft_strlen(info.minus_mod)));
			clean_up(&info);
			set_struc(&info);
			str += 1;
		}
		else
		{
			write(1, str, 1);
			info.charcount += 1;
			str++;
		}
	}
	va_end(info.list);
	return (info.charcount);
}
