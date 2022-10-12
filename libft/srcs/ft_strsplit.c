/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccariou <ccariou@hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 22:01:34 by ccariou           #+#    #+#             */
/*   Updated: 2022/09/09 11:52:12 by ccariou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static void	freearray(char **str, int len)
{
	while (len)
	{
		len --;
		free(str[len]);
		str[len] = 0;
	}
	free(str);
}

static int	count_w(char const *s, char c)
{
	int		i;
	int		cw;

	i = 0;
	cw = 0;
	while (s[i])
	{
		while (s[i] != '\0' && s[i] == c)
			i ++;
		if (s[i] != c && s[i])
			cw ++;
		while (s[i] != '\0' && s[i] != c)
			i ++;
	}
	return (cw);
}

static int	count_l(char const *s, char c)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (s[i] && s[i] == c)
		i ++;
	while (s[i] != '\0' && s[i] != c)
	{
		i ++;
		len ++;
	}
	return (len);
}

static char	*next(char const *s, char c)
{
	while (*s && *s == c)
		s ++;
	return ((char *)s);
}

char	**ft_strsplit(char const *s, char c)
{
	int		j;
	int		len;
	char	**tab;

	len = count_w(s, c);
	tab = (char **)malloc(sizeof(char *) * len + 1);
	if (tab == NULL || s == NULL)
		return (NULL);
	j = 0;
	while (len > j)
	{
		s = next(s, c);
		tab[j] = ft_strsub(s, 0, count_l(s, c));
		if (tab[j] == NULL)
		{
			freearray(tab, j);
			return (NULL);
		}
		j ++;
		s += count_l(s, c);
	}
	tab[j] = 0;
	return (tab);
}
