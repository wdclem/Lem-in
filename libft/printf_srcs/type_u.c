/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_u.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccariou <ccariou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 11:01:07 by ccariou           #+#    #+#             */
/*   Updated: 2022/09/09 11:56:18 by ccariou          ###   ########.fr       */
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

int	type_unsigned(t_info *info)
{
	unsigned long long	i;
	int					len;

	i = 0;
	i = change_size(info, i);
	if (!edge_case(info, i))
		convert(info, i, 10);
	len = info->precision - info->copylen + 1;
	if (len <= 0)
		return (1);
	info->mod = ft_strnew(len);
	if (info->mod == NULL)
		return (1);
	ft_memset(info->mod, '0', len);
	info->mod[len - 1] = '\0';
	return (0);
}
