/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 13:53:52 by jcameira          #+#    #+#             */
/*   Updated: 2023/10/03 14:05:59 by jcameira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *str)
{
	int		str_len;
	char	*new_str;

	str_len = ft_strlen(str) + 1;
	new_str = malloc(sizeof (char) * str_len);
	if (!new_str)
		return (NULL);
	new_str = ft_memcpy(new_str, str, str_len);
	return (new_str);
}
