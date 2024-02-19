/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utoa.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 00:16:59 by jcameira          #+#    #+#             */
/*   Updated: 2023/11/02 18:50:35 by jcameira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*utoa(unsigned int nbr)
{
	int					n_len;
	unsigned int		tmp_nbr;
	char				*nbr_str;

	n_len = num_len(nbr);
	tmp_nbr = nbr;
	nbr_str = malloc(sizeof (char) * (n_len + 1));
	if (!nbr_str)
		return (NULL);
	if (tmp_nbr == 0)
	{
		nbr_str[0] = '0';
		nbr_str[1] = '\0';
		return (nbr_str);
	}
	nbr_str[n_len] = '\0';
	while (tmp_nbr > 0)
	{
		nbr_str[--n_len] = (tmp_nbr % 10) + '0';
		tmp_nbr /= 10;
	}
	return (nbr_str);
}
