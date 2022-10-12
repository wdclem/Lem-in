/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_p.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccariou <ccariou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 16:24:35 by ccariou           #+#    #+#             */
/*   Updated: 2022/09/09 11:56:17 by ccariou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/../includes/ft_printf.h"

static void	make_adress(t_info *info)
{
	int	size;

	size = info->precision - info->copylen;
	if (size > 2)
	{
		size += 1;
		info->mod = ft_strnew(size);
		if (info->mod == NULL)
			return ;
		ft_memset(info->mod, '0', size);
	}
	else
		info->mod = ft_strnew(2);
	if (info->mod == NULL)
		return ;
	ft_strncpy(info->mod, "0x", 2);
}

int	type_p(t_info *info)
{
	long long	i;

	i = 0;
	i = va_arg(info->list, unsigned long);
	if (!edge_case(info, i))
		convert(info, i, 16);
	make_adress(info);
	return (0);
}
