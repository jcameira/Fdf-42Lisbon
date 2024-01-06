/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 13:18:45 by jcameira          #+#    #+#             */
/*   Updated: 2023/10/05 00:30:42 by jcameira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *substr, size_t len)
{
	size_t	i;
	size_t	j;

	if (!str && !substr)
		return (NULL);
	if (substr == str || ft_strlen(substr) == 0)
		return ((char *)str);
	i = 0;
	while (i < len && str[i])
	{
		j = 0;
		while (str[i + j] && substr[j] && str[i + j] == substr[j]
			&& (i + j) < len)
			j++;
		if (!substr[j])
			return ((char *)(str + i));
		i++;
	}
	return (NULL);
}
