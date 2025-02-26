/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_by_spaces.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 15:20:07 by nholbroo          #+#    #+#             */
/*   Updated: 2025/02/23 11:15:25 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

/*
ft_count_words():
Takes a string str as parameter. Its purpose is
to count the number of words in the given string, where words are separated by
whitespaces.
*/
static size_t	ft_count_words(const char *str)
{
	size_t	count;
	size_t	i;

	count = 0;
	i = 0;
	while (str[i])
	{
		while (str[i] == ' ' || str[i] == '\t')
			i++;
		if (str[i])
			count++;
		while (str[i] && str[i] != ' ' && str[i] != '\t')
			i++;
	}
	return (count);
}

/*
Extracts a substring from the input string str starting from the beginning until
it encounters a space or reaches the end of the string. The
function dynamically allocates memory for the extracted substring, copies the
characters from the input string to the newly allocated memory, and appends a
null terminator.
*/
static char	*ft_extract_word(const char *str)
{
	char	*word;
	int		i;
	int		len;

	len = 0;
	while (str[len] && str[len] != ' ' && str[len] != '\t')
		len++;
	word = (char *)malloc(sizeof(char) * (len + 1));
	if (!word)
		return (NULL);
	i = 0;
	while (i < len)
	{
		word[i] = str[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

/*
Uses ft_extract_word() and stores extracted word at the i-th position in the
array of string arrays. If the extraction is not successful, it cleans up the
previously allocated memory (substrings and array) and returns NULL.
*/
static char	*ft_word_into_array(const char *str, size_t i, char **arr)
{
	if (!str)
		return (NULL);
	arr[i] = ft_extract_word(str);
	if (!arr[i])
	{
		while (i > 0)
		{
			i--;
			free(arr[i]);
		}
		free(arr);
		return (NULL);
	}
	return (arr[i]);
}

/*
ft_split() returns an array of strings ('array of arrays' since strings are an
arrays of characters terminated by '\0').
The function takes the input string s and splits it into an array containing each
of its words. Words are separated by one or more whitespaces.
To facilitate easy iteration over the array
of words, an extra element is allocated and set to a NULL pointer, allowing a
simple loop condition just like to checking a NULL char in a string:
while (word_arr[i] != NULL).
*/
char	**ft_split_by_spaces(const char *s)
{
	size_t	nb_words;
	size_t	i;
	char	**word_arr;

	if (!s)
		return (NULL);
	nb_words = ft_count_words(s);
	word_arr = malloc(sizeof(char *) * (nb_words + 1));
	if (!word_arr)
		return (NULL);
	i = -1;
	while (++i < nb_words)
	{
		while (*s && (*s == ' ' || *s == '\t'))
			s++;
		if (*s == '#')
			break ;
		word_arr[i] = ft_word_into_array(s, i, word_arr);
		if (word_arr[i] == NULL)
			return (NULL);
		while (*s && *s != ' ' && *s != '\t')
			s++;
	}
	word_arr[i] = NULL;
	return (word_arr);
}
