/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bitmask_single.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccariou <ccariou@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 16:47:35 by ccariou           #+#    #+#             */
/*   Updated: 2023/02/03 17:51:14 by ccariou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int	bitmask_check_idx(t_bitmask *mask, int idx)
{
	return (mask->bits[idx / PAGE_SIZE] & (1 << (idx % PAGE_SIZE)));
}

void	bitmask_set_idx(t_bitmask *mask, int idx)
{
	mask->bits[idx / PAGE_SIZE] |= (1 << (idx % PAGE_SIZE));
	if (idx / (int)PAGE_SIZE > mask->last_page)
		mask->last_page = idx / PAGE_SIZE;
}

void	bitmask_clear_idx(t_bitmask *mask, int idx)
{
	mask->bits[idx / PAGE_SIZE] &= ~(1 << (idx % PAGE_SIZE));
}
