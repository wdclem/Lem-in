/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bittricks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccariou <ccariou@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 16:47:35 by ccariou           #+#    #+#             */
/*   Updated: 2023/02/03 17:51:14 by ccariou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "lemin.h"

int bitmask_check_idx(t_bitmask *mask, int idx)
{
	return (mask->bits[idx / PAGE_SIZE] & (1 << (idx % PAGE_SIZE)));
}

void bitmask_set_idx(t_bitmask *mask, int idx)
{
	mask->bits[idx / PAGE_SIZE] |= (1 << (idx % PAGE_SIZE));
	if (idx / (int)PAGE_SIZE > mask->last_page)
		mask->last_page = idx / PAGE_SIZE;
}

void bitmask_add(t_bitmask *src, t_bitmask *dst)
{
	int	page_idx;

	page_idx = 0;
	while (page_idx <= src->last_page)
	{
		dst->bits[page_idx] |= src->bits[page_idx];
		page_idx += 1;
	}
	dst->last_page = ft_max(src->last_page, dst->last_page);
}

int bitmask_compare(t_bitmask *left, t_bitmask *right)
{
	int	page_idx;
	int	last_page;

	page_idx = 0;
	last_page = ft_min(left->last_page, right->last_page);
	while (page_idx <= last_page)
	{
		if (left->bits[page_idx] & right->bits[page_idx])
			return (1);
		page_idx++;
	}
	return (0);
}

void	bitmask_clear(t_bitmask *mask)
{
	ft_bzero((void *)&mask->bits, sizeof(int) * mask->last_page);
	mask->last_page = 0;
}
