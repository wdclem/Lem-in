/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccariou <ccariou@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 17:58:04 by ccariou           #+#    #+#             */
/*   Updated: 2023/01/10 12:28:35 by ccariou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

/* ready in case
t_room	*room_init()
{
	link_count;
	*id = NULL
	int				x;
	int				y;
	int				visited;
	int				valid;
	struct s_link	*link;
	struct s_room	*next;
	size_t			alloced;
}
*/
t_hasht	*table_init(void)
{
	t_hasht		*table;

	table = (t_hasht *)malloc(sizeof(t_hasht));
	if (!table)
		return (NULL);
	table->room = (t_room **)malloc(sizeof(t_room*) * HT_CAP);
	if (!table->room)
		return (NULL);
	ft_bzero(table->room, sizeof(HT_CAP));
	return (table);
}
