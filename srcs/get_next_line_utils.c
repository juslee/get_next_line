/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welee <welee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 14:37:29 by welee             #+#    #+#             */
/*   Updated: 2024/09/19 18:31:48 by welee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file get_next_line_utils.c
 * @brief Utility functions for get_next_line
 */

#include <stdlib.h>
#include <stddef.h>
#include "get_next_line.h"

/**
 * @brief Returns the length of a string.
 *
 * @param s The string to measure.
 * @return The length of the string.
 */
size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s && s[i])
		i++;
	return (i);
}

/**
 * @brief Returns a pointer to the first occurrence of the character c
 * in the string s.
 *
 * @param s The string to search.
 * @param c The character to find.
 * @return A pointer to the matched character or NULL if the character is not
 * found.
 */
char	*ft_strchr(const char *s, int c)
{
	if (!s)
		return (NULL);
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if (c == '\0')
		return ((char *)s);
	return (NULL);
}

/**
 * @brief Concatenates two strings.
 *
 * @param s1 The first string.
 * @param s2 The second string.
 * @return A newly allocated string containing the concatenation of s1 and s2.
 */
char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*joined;
	size_t	i;
	size_t	j;

	joined = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!joined)
		return (NULL);
	i = 0;
	while (s1 && s1[i])
	{
		joined[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2 && s2[j])
		joined[i++] = s2[j++];
	joined[i] = '\0';
	return (joined);
}

/**
 * @brief Append a copy of the null-terminated string src to the end of the
 * null-terminated string dest.
 * @param dest The destination string.
 * @param src The source string.
 * @return The destination string.
 */
char	*ft_strcat(char *dest, const char *src)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (dest[i])
		++i;
	j = 0;
	while (src[j])
	{
		dest[i] = src[j];
		++i;
		++j;
	}
	dest[i] = '\0';
	return (dest);
}

/**
 * @brief Returns a substring of the string s.
 *
 * @param s The string to extract from.
 * @param start The starting index of the substring.
 * @param len The length of the substring.
 * @return A newly allocated substring of s.
 */
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*sub;

	if (!s || ft_strlen(s) < start || len <= 0
		|| !s[start] || start + len > ft_strlen(s) + 1)
		return (NULL);
	i = 0;
	sub = (char *)malloc(len + 1);
	if (!sub)
		return (NULL);
	while (s[start + i] && i < len)
	{
		sub[i] = s[start + i];
		i++;
	}
	sub[i] = '\0';
	return (sub);
}
