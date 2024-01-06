/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 14:10:45 by jcameira          #+#    #+#             */
/*   Updated: 2023/10/04 00:55:26 by jcameira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *str1, char const *str2)
{
	size_t	str_len1;
	size_t	str_len2;
	char	*new_str;

	str_len1 = ft_strlen(str1);
	str_len2 = ft_strlen(str2);
	new_str = malloc(sizeof (char) * (str_len1 + str_len2 + 1));
	if (!new_str)
		return (NULL);
	ft_memmove((void *)(new_str), str1, str_len1);
	ft_memmove((void *)(new_str + str_len1), str2, str_len2);
	new_str[str_len1 + str_len2] = '\0';
	return (new_str);
}
