/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccariou <ccariou@hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 16:36:40 by ccariou           #+#    #+#             */
/*   Updated: 2022/09/09 11:51:54 by ccariou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static int	intlen(int n)
{
	int	len;

	len = 0;
	while (n > 0)
	{
		n /= 10;
		len ++;
	}
	return (len);
}

static char	*printc(char *str, int len, int neg, int n)
{
	str[len] = '\0';
	while (len > 0)
	{
		len --;
		str[len] = n % 10 + '0';
		n = n / 10;
	}
	if (neg > 0)
		str[0] = '-';
	return (str);
}

char	*ft_itoa(int n)
{
	int		len;
	int		isneg;
	char	*str;

	isneg = 0;
	if (n < 0)
	{
		isneg = 1;
		n *= -1;
	}
	if (n == 0)
		return (ft_strdup("0"));
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	len = intlen(n) + isneg;
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (str == NULL)
		return (NULL);
	str = printc(str, len, isneg, n);
	return (str);
}
