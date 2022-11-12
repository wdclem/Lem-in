/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maps.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccariou <ccariou@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 17:05:03 by ccariou           #+#    #+#             */
/*   Updated: 2022/10/24 17:05:09 by ccariou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

	char		*line;
	int			s;
	t_parser	p;
	t_lexer		l;

	while ((s = ft_get_next_line(0, &line)) > 0)
	{
		if (s - 1 <= 0)
		{
			free(line);
			continue ;
		}
		if (INPUT)
			ft_putendl(line);
		l = new_lexer(line, s - 1);
		p = new_parser(&l);
		parser_parse(&p, data);
	}
	if (s < 0)
	{
		ft_putendl_fd("Error: Failed to read", 2);
		exit(1);
	}
	validate_data(*data);
}
