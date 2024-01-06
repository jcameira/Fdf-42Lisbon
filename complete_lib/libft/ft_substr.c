/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 14:06:34 by jcameira          #+#    #+#             */
/*   Updated: 2023/10/04 23:05:44 by jcameira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *str, unsigned int start, size_t len)
{
	char	*substr;

	if (!str)
		return (NULL);
	if (len >= ft_strlen(str) - start)
		len = ft_strlen(str) - start;
	if (start > ft_strlen(str))
		len = 0;
	substr = malloc(sizeof (char) * (len + 1));
	if (!substr)
		return (NULL);
	substr = ft_memcpy(substr, (const void *)(str + start), len);
	substr[len] = '\0';
	return (substr);
}
