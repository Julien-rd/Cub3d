/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jromann <jromann@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 10:46:40 by jromann           #+#    #+#             */
/*   Updated: 2026/01/07 12:07:59 by jromann          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_wordcount(char const *s, char c)
{
	int	i;
	int	b;
	int	wordcount;

	i = -1;
	b = 0;
	wordcount = 0;
	while (s[++i])
	{
		if (s[i] == c && b == 1)
			b = 0;
		else if (!(s[i] == c) && b == 0)
		{
			wordcount++;
			b = 1;
		}
	}
	return (wordcount);
}

static int	ft_substrlen(char const *s1, char c)
{
	int	i;
	int	length;

	i = -1;
	length = 0;
	while (s1[++i])
	{
		if (s1[i] == c)
			return (length);
		length++;
	}
	return (length);
}

static char	*ft_create_array(int length, char const *s)
{
	char	*arr;
	int		k;
	int		index;
	int		i;

	index = 0;
	k = -1;
	length += 1;
	i = -1;
	arr = (char *)malloc(sizeof(char) * length);
	if (!arr)
		return (NULL);
	while (--length > 0)
		arr[++k] = s[index++];
	arr[++k] = 0;
	return (arr);
}

static char	**ft_cleanup(char **arr)
{
	int	i;

	i = -1;
	while (arr[++i])
		free(arr[i]);
	free(arr);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	int		wordcount;
	int		i;
	int		index;
	int		length;
	char	**arr;

	wordcount = ft_wordcount(s, c);
	i = -1;
	index = 0;
	arr = (char **)ft_calloc(sizeof(char *), (wordcount + 1));
	while (wordcount > 0 && arr)
	{
		length = ft_substrlen(&s[index], c);
		if (length)
		{
			arr[++i] = ft_create_array(length, &s[index]);
			if (!arr[i])
				return (ft_cleanup(arr));
			wordcount--;
			index += (length - 1);
		}
		index++;
	}
	return (arr);
}
