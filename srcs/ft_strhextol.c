/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strhextol.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 19:21:49 by jcameira          #+#    #+#             */
/*   Updated: 2024/02/21 02:01:44 by jcameira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

static int	strpos(char c, char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (c == str[i])
			return (i);
	}
	return (-1);
}

long	ft_strhextol(char *str)
{
	int			i;
	long int	n;

	n = 0;
	i = -1;
	while (str[++i])
	{
		n *= 16;
		n += strpos(ft_toupper(str[i]), HEX);
	}
	return (n);
}
