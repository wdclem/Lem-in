/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_c.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccariou <ccariou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 11:04:38 by ccariou           #+#    #+#             */
/*   Updated: 2022/09/09 11:56:16 by ccariou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/../includes/ft_printf.h"

int	type_c(t_info *info)
{
	info->copy = ft_strnew(1);
	if (info->copy == NULL)
		return (1);
	*info->copy = (char)va_arg(info->list, int);
	if (info->copy[0] == '\0')
		info->cnull = 1;
	info->copylen = 1;
	return (0);
}
