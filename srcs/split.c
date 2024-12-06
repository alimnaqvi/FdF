/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaqvi <anaqvi@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 16:51:56 by anaqvi            #+#    #+#             */
/*   Updated: 2024/12/06 10:29:40 by anaqvi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static size_t	count_words(char const *s, char c)
{
	size_t	count;
	int		in_word;

	count = 0;
	in_word = 0;
	while (*s)
	{
		if (*s != c && !in_word)
		{
			in_word = 1;
			count++;
		}
		else if (*s == c)
			in_word = 0;
		s++;
	}
	return (count);
}

static char	*get_next_word(char const **s, char c, t_list **allocs)
{
	char		*word;
	size_t		len;
	char const	*start;

	start = *s;
	len = 0;
	while (**s && **s != c)
	{
		len++;
		(*s)++;
	}
	word = (char *)ft_malloc(sizeof(char) * (len + 1), allocs);
	if (word)
		ft_strlcpy(word, start, len + 1);
	return (word);
}

static char	**free_result(char **result, size_t i)
{
	while (i > 0)
	{
		i--;
		free(result[i]);
	}
	free(result);
	return (NULL);
}

char	**ft_split_safe(char const *s, char c, t_list **allocs)
{
	char	**result;
	size_t	word_count;
	size_t	i;

	if (!s)
		return (NULL);
	word_count = count_words(s, c);
	result = (char **)ft_malloc(sizeof(char *) * (word_count + 1), allocs);
	if (!result)
		return (NULL);
	i = 0;
	while (*s)
	{
		if (*s != c)
		{
			result[i] = get_next_word(&s, c, allocs);
			if (!result[i])
				return (free_result(result, i));
			i++;
		}
		else
			s++;
	}
	result[i] = NULL;
	return (result);
}
