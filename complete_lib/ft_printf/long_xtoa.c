/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   long_xtoa.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 01:10:35 by jcameira          #+#    #+#             */
/*   Updated: 2023/10/30 01:42:15 by jcameira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	long_hex_len(unsigned long int nbr)
{
	int	len;

	len = 0;
	if (nbr == 0)
		return (1);
	while (nbr >= 1)
	{
		len++;
		nbr /= 16;
	}
	return (len);
}

char	*long_xtoa(unsigned long int nbr, int uppercase)
{
	int					n_len;
	unsigned long int	tmp_nbr;
	char				*nbr_str;

	n_len = long_hex_len(nbr);
	tmp_nbr = nbr;
	nbr_str = malloc(sizeof (char) * (n_len + 1));
	if (!nbr_str)
		return (NULL);
	if (nbr == 0)
	{
		nbr_str[0] = '0';
		nbr_str[1] = '\0';
		return (nbr_str);
	}
	nbr_str[n_len] = '\0';
	while (tmp_nbr > 0)
	{
		if (uppercase)
			nbr_str[--n_len] = HEX_UPPER[tmp_nbr % 16];
		else
			nbr_str[--n_len] = HEX_LOWER[tmp_nbr % 16];
		tmp_nbr /= 16;
	}
	return (nbr_str);
}
