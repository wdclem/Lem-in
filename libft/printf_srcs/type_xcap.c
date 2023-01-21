/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   typexcap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccariou <ccariou@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 16:06:07 by ccariou           #+#    #+#             */
/*   Updated: 2022/09/09 11:56:18 by ccariou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/../includes/ft_printf.h"

static void	capital(char *str)
{
	while (*str)
	{
		*str = ft_toupper(*str);
		str++;
	}
}

int	type_xcap(t_info *info)
{
	type_x(info);
	capital(info->copy);
	capital(info->mod);
	return (0);
}
