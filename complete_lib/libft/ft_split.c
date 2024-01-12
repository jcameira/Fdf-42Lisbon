/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 14:45:23 by jcameira          #+#    #+#             */
/*   Updated: 2024/01/12 12:11:35 by jcameira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	word_count(char const *str, char c)
{
	int	i;
	int	words;

	i = 0;
	words = 0;
	while (str[i])
	{
		while (str[i] && (str[i] == c))
			i++;
		if (str[i] && str[i++] != c)
			words++;
		while (str[i] && str[i] != c)
			i++;
	}
	return (words);
}

static void	*free_matrix(char **matrix, int word)
{
	while (word >= 0)
	{
		free(matrix[word]);
		matrix[word] = NULL;
		word--;
	}
	free(matrix);
	return (NULL);
}

static void	*fill_matrix(char **matrix, char const *str, char c)
{
	int		i;
	int		j;
	int		word;

	i = 0;
	word = 0;
	while (str[i])
	{
		if (str[i] && (str[i] == c))
			i++;
		else
		{
			j = 0;
			while (str[i + j] && str[i + j] != c)
				j++;
			matrix[word++] = ft_substr(str, i, j);
			if (!matrix[word - 1])
				return (free_matrix(matrix, word - 1));
			i += j;
		}
	}
	matrix[word] = 0;
	return (matrix);
}

char	**ft_split(char const *str, char c)
{
	char	**matrix;

	matrix = (char **)malloc(sizeof (char *) * (word_count(str, c) + 1));
	if (!matrix)
		return (NULL);
	matrix = fill_matrix(matrix, str, c);
	return (matrix);
}
