/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bitmask_group.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccariou <ccariou@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 16:47:35 by ccariou           #+#    #+#             */
/*   Updated: 2023/02/03 17:51:14 by ccariou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	bitmask_add(t_bitmask *src, t_bitmask *dst)
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

void	bitmask_remove(t_bitmask *src, t_bitmask *dst)
{
	int	page_idx;

	page_idx = 0;
	while (page_idx <= src->last_page)
	{
		dst->bits[page_idx] &= ~(src->bits[page_idx]);
		page_idx += 1;
	}
}

int	bitmasks_are_equal(t_bitmask *left, t_bitmask *right)
{
	int	page_idx;
	int	last_page;

	page_idx = 0;
	last_page = ft_max(left->last_page, right->last_page);
	while (page_idx <= last_page)
	{
		if ((left->bits[page_idx] & right->bits[page_idx]) != \
			left->bits[page_idx] || (left->bits[page_idx] & \
			right->bits[page_idx]) != right->bits[page_idx])
			return (0);
		page_idx++;
	}
	return (1);
}

void	bitmask_clear(t_bitmask *mask)
{
	ft_bzero((void *)&mask->bits, sizeof(int) * (mask->last_page + 1));
	mask->last_page = 0;
}
