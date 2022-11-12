/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccariou <ccariou@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 14:59:25 by ccariou           #+#    #+#             */
/*   Updated: 2022/11/10 20:53:31 by ccariou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEMIN_H
# define LEMIN_H

#include "libft.h"
#include <stdio.h> // TO BE REMOVE

typedef struct s_info{
	int		room;
	int		link;
	int		ants;
	char	**str;
}				t_info;

typedef struct s_room{
	int		id;
	int		start;
	int		end;
	int		links;
}				t_room;

typedef struct s_pointer{
}				t_pointer

typedef struct s_id{
}				t_id
typedef struct 

int	main();
int	get_info(t_info *info);

#endif