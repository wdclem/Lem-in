/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_percent.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccariou <ccariou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 11:04:06 by ccariou           #+#    #+#             */
/*   Updated: 2022/09/09 11:56:17 by ccariou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/../includes/ft_printf.h"

int	type_percent(t_info *info)
{
	info->copy = ft_strnew(1);
	if (info->copy == NULL)
		return (1);
	info->copy[0] = '%';
	info->copylen = 1;
	return (0);
}
