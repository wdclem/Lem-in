/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpolonen <tpolonen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 16:40:43 by tpolonen          #+#    #+#             */
/*   Updated: 2021/12/13 14:18:15 by tpolonen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static size_t	count_words(char const *s, char c)
{
	size_t	count;

	count = 0;
	while (*s)
	{
		while (*s == c && *s)
			s++;
		if (*s)
			count++;
		while (*s != c && *s)
			s++;
	}
	return (count);
}

static int	free_str_tab(char ***tab, int count)
{
	int	i;

	i = 0;
	while (i < count)
		free(*tab[i++]);
	free(*tab);
	return (0);
}

static int	cut_word(char const *string, char delimiter, char **tab, int i)
{
	char const	*stop;
	char		*word;

	stop = ft_strchr(string, delimiter);
	if (stop == NULL)
		stop = string + ft_strlen(string);
	word = ft_strsub(string, 0, (size_t)(stop - string));
	if (!word)
		return (free_str_tab(&tab, i));
	tab[i] = word;
	return (1);
}

char	**ft_strsplit(char const *string, char delimiter)
{
	int		i;
	char	**words;

	words = (char **) malloc(sizeof(char *) * \
			(count_words(string, delimiter) + 1));
	if (!words)
		return (NULL);
	i = 0;
	while (string != NULL && *string)
	{
		while (*string == delimiter && *string)
			string++;
		if (*string)
		{
			if (!cut_word(string, delimiter, words, i))
				return (NULL);
			i++;
			string = ft_strchr(string, delimiter);
		}
	}
	words[i] = NULL;
	return (words);
}
