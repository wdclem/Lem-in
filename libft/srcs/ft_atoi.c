/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccariou <ccariou@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 21:43:39 by ccariou           #+#    #+#             */
/*   Updated: 2022/09/09 11:51:48 by ccariou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"
/* alpha to integer, tranform char *str to a int
 */

int	ft_atoi(const char *str)
{
	int	i;
	int	isneg;
	int	numb;

	i = 0;
	isneg = 0;
	numb = 0;
	while ((str[i] > 8 && str[i] <= 20) || str[i] == ' ')
		i ++;
	if (str[i] == '-')
		isneg = 1;
	if (str[i] == '+' || str[i] == '-')
		i ++;
	while (str[i] >= '0' && str[i] <= '9' && str[i] != '\0')
	{
		numb = numb * 10 + (str[i] - '0');
		i ++;
	}
	if (isneg == 1)
		return (numb * -isneg);
	else
		return (numb);
}
