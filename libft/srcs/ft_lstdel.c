/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccariou <ccariou@hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 14:27:56 by ccariou           #+#    #+#             */
/*   Updated: 2022/09/09 11:51:55 by ccariou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list	*todel;
	t_list	*extra;

	todel = *alst;
	extra = *alst;
	while (todel)
	{
		todel = (*alst)->next;
		ft_lstdelone(&*alst, del);
		*alst = todel;
	}
	*alst = extra;
	*alst = NULL;
}
