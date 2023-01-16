/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpolonen <tpolonen@student.hive.fi>          +#+  +:+       +#+      */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 14:59:25 by tpolonen           #+#    #+#            */
/*   Updated: 2023/01/16 18:30:07 by tpolonen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"
#include "libft.h"

/* q should be a null pointer */
int	open_path(t_path **path, int len)
{
	t_path		*new_path;

	new_path = (t_path *)ft_memalloc(sizeof(t_path));
	if (!new_path)
		return (-1);
	reserve_path(&new_path, len);
	*path = new_path;
	return (1);
}

int	reserve_path(t_path **path, int len)
{
	t_link	**new_arr;
	int		new_size;

	if ((*path)->alloced >= len * (int)sizeof(t_link *))
		return (1);
	new_size = (*path)->alloced;
	while (new_size < len * (int)sizeof(t_link))
		new_size *= 2;
	new_arr = (t_link **)ft_memalloc(new_size);
	if (!new_arr)
		return (-1);
	ft_memcpy((void *)new_arr, (void *)(*path)->arr, (*path)->alloced);
	ft_memdel((void **)&(*path)->arr);
	(*path)->arr = new_arr;
	(*path)->alloced = new_size;
	(*path)->len = len;
	return (1);
}

void	set_path_step(t_path **path, t_link* link, int index)
{
	t_link	**ptr;

	ptr = *(&(*path)->arr + index);
	*ptr = link;
}

void	close_path(t_path **path)
{
	ft_memdel((void **)&(*path)->arr);
	ft_memdel((void **)path);
}
