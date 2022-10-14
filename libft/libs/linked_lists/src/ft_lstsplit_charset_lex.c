/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsplit_charset_lex.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilandols <ilyes@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 12:40:35 by ilandols          #+#    #+#             */
/*   Updated: 2022/10/14 13:15:43 by ilandols         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/linked_lists.h"

static int	is_charset(char c, char *charset)
{
	int	i;

	i = 0;
	while (charset[i])
	{
		if (c == charset[i])
			return (1);
		i++;
	}
	return (0);
}

static int	get_size_word(char const *s, char *charset, int index)
{
	int	result;

	result = 0;
	if (s[index] && is_charset(s[index], charset))
	{
		index++;
		return (1);
	}
	while (s[index] && !is_charset(s[index], charset))
	{
		result++;
		index++;
	}
	return (result);
}

static char	*get_word(char const *s, char *charset, int *index, int size_word)
{
	int		j;
	char	*result;

	j = 0;
	result = malloc((size_word + 1) * sizeof(char));
	if (!result)
		return (NULL);
	if (s[*index] && is_charset(s[*index], charset))
	{
		result[j] = s[*index];
		result[j + 1] = '\0';
		*index += 1;
		return (result);
	}
	while (s[*index] && !is_charset(s[*index], charset))
	{
		result[j] = s[*index];
		j++;
		*index += 1;
	}
	result[j] = '\0';
	return (result);
}

static int	count_words(char const *s, char *charset)
{
	int	result;
	int	i;

	if (!s || !s[0])
		return (0);
	if (!charset)
		return (1);
	result = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] && is_charset(s[i], charset))
			result++;
		else if (s[i] && !is_charset(s[i], charset)
			&& is_charset(s[i + 1], charset))
			result++;
		i++;
	}
	if (!is_charset(s[i - 1], charset))
		result++;
	return (result);
}

t_lex	*ft_lstsplit_charset_lex(char const *s, char *charset)
{
	t_lex	*lst;	
	int		words;
	int		i;
	int		j;
	int		size;

	lst = NULL;
	words = count_words(s, charset);
	i = 0;
	j = 0;
	while (i < words)
	{
		size = get_size_word(s, charset, j);
		ft_lstadd_back_lex(&lst, ft_lstnew_lex(get_word(s, charset, &j, size)));
		if (!ft_lstis_correct_lex(lst, i + 1))
		{
			ft_lstclear_lex(&lst);
			return (NULL);
		}
		i++;
	}
	return (lst);
}
