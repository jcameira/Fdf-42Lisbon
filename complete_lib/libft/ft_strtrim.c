/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 14:29:42 by jcameira          #+#    #+#             */
/*   Updated: 2024/02/20 10:19:01 by jcameira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check_charset(char c, char const *charset)
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

char	*ft_strtrim(char const *str, char const *charset)
{
	size_t	start;
	size_t	end;
	char	*new_str;

	if (!str || !charset)
		return (NULL);
	start = 0;
	end = ft_strlen(str);
	while (str[start] && check_charset(str[start], charset))
		start++;
	while (str[end - 1] && check_charset(str[end - 1], charset) && end > start)
		end--;
	new_str = malloc(sizeof (char) * (end - start + 1));
	if (!new_str)
		return (NULL);
	ft_strlcpy(new_str, &str[start], end - start + 1);
	return (new_str);
}
