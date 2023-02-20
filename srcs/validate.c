/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccariou <ccariou@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 12:43:53 by ccariou           #+#    #+#             */
/*   Updated: 2023/02/13 17:10:22 by ccariou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static long	ft_strtol(const char *nptr, char **endptr)
{
	long	n;
	int		sign;

	n = 0;
	sign = 1;
	while (ft_isspace(*nptr))
		nptr++;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			sign = -1;
		nptr++;
	}
	while (ft_isdigit(*nptr))
		n = (10 * n) + ((long) sign * (*nptr++ - '0'));
	if (*endptr != NULL)
		*endptr = (char *)nptr;
	return (n);
}

int	validate_string_is_integer(char *str)
{
	int		i;
	int		neg;
	long	num;
	char	*endptr;

	i = 0;
	neg = 0;
	if (str[i] == '-')
		neg = 1;
	else if (!ft_isdigit(str[i]))
		return (ERROR);
	while (str[i + neg])
	{
		if (!ft_isdigit(str[i + neg]))
			return (ERROR);
		i++;
	}
	if (i + neg > 10)
		return (ERROR);
	num = ft_strtol(str, &endptr);
	if (num > FT_INT_MAX || num < FT_INT_MIN)
		return (ERROR);
	return (1);
}

int	count_amount_of_chars_in_str(char *name, char c)
{
	int	idx;
	int	count;

	idx = 0;
	count = 0;
	while (name[idx])
	{
		count += name[idx] == c;
		idx++;
	}
	return (count);
}
