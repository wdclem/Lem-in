/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccariou <ccariou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 14:36:22 by ccariou           #+#    #+#             */
/*   Updated: 2022/09/09 11:52:13 by ccariou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static int	ft_dup_result(int fd, char **line, char **result)
{
	int		i;
	char	*tmp;

	i = 0;
	while (result[fd][i] != '\n' && result[fd][i] != '\0')
		i++;
	if (result[fd][i] == '\n')
	{
		*line = ft_strsub(result[fd], 0, i);
		tmp = ft_strdup(result[fd] + i + 1);
		if (tmp == NULL || line == NULL)
			return (1);
		ft_strdel(&result[fd]);
		result[fd] = tmp;
		if (result[fd][0] == '\0')
			ft_strdel(&result[fd]);
	}
	else
	{
		*line = ft_strdup(result[fd]);
		if (line == NULL)
			return (1);
		ft_strdel(&result[fd]);
	}
	return (1);
}

static int	ft_output(char **result, char **line, int bytes, const int fd)
{
	if (bytes < 0)
	{
		ft_strdel(result);
		return (-1);
	}
	if (!bytes && !result[fd])
	{
		ft_strdel(result);
		return (0);
	}
	return (ft_dup_result(fd, line, result));
}

int	get_next_line(const int fd, char **line)
{
	static char	*result[FD_SIZE];
	char		*tmp;
	char		buff[BUFF_SIZE + 1];
	int			bytes;

	if (fd < 0 || line == NULL || read(fd, buff, 0) < 0)
		return (-1);
	bytes = read(fd, buff, BUFF_SIZE);
	while (bytes > 0)
	{
		buff[bytes] = '\0';
		if (!result[fd])
			result[fd] = ft_strnew(1);
		if (result[fd] == NULL)
			return (1);
		tmp = ft_strjoin(result[fd], buff);
		if (tmp == NULL)
			return (1);
		ft_strdel(&result[fd]);
		result[fd] = tmp;
		if (ft_strchr(buff, '\n'))
			break ;
		bytes = read(fd, buff, BUFF_SIZE);
	}
	return (ft_output(result, line, bytes, fd));
}
