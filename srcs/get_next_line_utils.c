/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welee <welee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 14:37:29 by welee             #+#    #+#             */
/*   Updated: 2024/05/03 15:34:26 by welee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file get_next_line_utils.c
 * @brief Utility functions for get_next_line
 */

#include <stdlib.h>
#include "get_next_line.h"

/**
 * @brief Locates the first occurrence of c (converted to a char) in the
 * string pointed to by s.
 * The terminating null character is considered to be part of the string;
 * therefore if c is `\0`, the functions locate the terminating `\0`.
 * @param s string to search in
 * @param c character to search for
 * @return the pointer to the located character, or NULL if the character
 * does not appear in the string
 */
char	*ft_strchr(const char *s, int c)
{
	unsigned int	i;
	char			cc;

	cc = (char) c;
	i = 0;
	while (s[i])
	{
		if (s[i] == cc)
			return ((char *) &s[i]);
		i++;
	}
	if (s[i] == cc)
		return ((char *) &s[i]);
	return (NULL);
}

/**
 * @brief Concatenate two strings.
 * @param s1 The first string.
 * @param s2 The second string.
 * @return The concatenated string.
 */
char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*result;
	size_t	s1_len;
	size_t	s2_len;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	result = (char *)malloc(s1_len + s2_len + 1);
	if (!result)
		return (NULL);
	ft_memcpy(result, s1, s1_len);
	ft_memcpy(result + s1_len, s2, s2_len);
	result[s1_len + s2_len] = 0;
	return (result);
}

/**
 * @brief Duplicate a string.
 * @param s The string to duplicate.
 * @return The duplicated string.
 */
char	*ft_strdup(const char *s)
{
	char	*dup;
	size_t	len;

	if (s == NULL)
		return (NULL);
	len = ft_strlen(s) + 1;
	dup = (char *)malloc(len);
	if (dup == NULL)
		return (NULL);
	ft_memcpy(dup, s, len);
	return (dup);
}

/**
 * @brief Calculate the length of a string
 * @param s The string to calculate the length
 * @return The length of the string
 */
size_t	ft_strlen(const char *s)
{
	size_t	len;

	if (!s)
		return (0);
	len = 0;
	while (s[len])
		++len;
	return (len);
}

/**
 * @brief Copy memory area
 * @param dst void pointer to the destination
 * @param src void pointer to the source
 * @param n number of bytes to copy
 * @return The original destination pointer
 */
void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*destination;
	unsigned char	*source;

	if (!dest && !src)
		return (NULL);
	destination = (unsigned char *)dest;
	source = (unsigned char *)src;
	while (n--)
		*destination++ = *source++;
	return (dest);
}
