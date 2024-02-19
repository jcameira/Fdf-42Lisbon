/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 00:44:24 by jcameira          #+#    #+#             */
/*   Updated: 2023/11/03 12:55:41 by jcameira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	write_ptr(char	*nbr_str, unsigned long int nbr, t_pf_flags *flags)
{
	int	counter;

	counter = 0;
	if (nbr == 0)
	{
		flags->precision = 5;
		counter += write_str("(nil)", flags);
		return (counter);
	}
	counter += write_str("0x", flags);
	counter += write_str(nbr_str, flags);
	return (counter);
}

int	print_ptr(unsigned long int nbr, t_pf_flags *flags)
{
	int		counter;
	char	*nbr_str;

	counter = 0;
	if (nbr == 0)
		flags->width -= 4;
	else
		flags->width -= 2;
	nbr_str = long_xtoa(nbr, 0);
	if (!nbr_str)
		return (0);
	if (flags->precision >= 0 && (size_t)flags->precision < ft_strlen(nbr_str))
		flags->precision = ft_strlen(nbr_str);
	if (flags->minus)
		counter += write_ptr(nbr_str, nbr, flags);
	counter += print_width(flags->width, long_hex_len(nbr), 0);
	if (!(flags->minus))
		counter += write_ptr(nbr_str, nbr, flags);
	free(nbr_str);
	return (counter);
}
