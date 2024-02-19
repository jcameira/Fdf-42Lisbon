/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_unsigned.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 00:11:20 by jcameira          #+#    #+#             */
/*   Updated: 2023/11/02 18:52:17 by jcameira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	write_unsigned(char *nbr_str, t_pf_flags *flags)
{
	int	counter;

	counter = 0;
	if (flags->precision >= 0)
		counter += print_width(flags->precision, ft_strlen(nbr_str), 1);
	counter += write_str(nbr_str, flags);
	return (counter);
}

int	flags_unsigned(char *nbr_str, t_pf_flags *flags)
{
	int	counter;

	counter = 0;
	if (flags->precision >= 0 && (size_t)flags->precision < ft_strlen(nbr_str))
		flags->precision = ft_strlen(nbr_str);
	if (flags->minus)
		counter += write_unsigned(nbr_str, flags);
	if (flags->precision >= 0)
	{
		flags->width -= flags->precision;
		counter += print_width(flags->width, 0, 0);
	}
	else
		counter += print_width(flags->width, ft_strlen(nbr_str), flags->zero);
	if (!(flags->minus))
		counter += write_unsigned(nbr_str, flags);
	return (counter);
}

int	print_unsigned(unsigned int nbr, t_pf_flags *flags)
{
	int		counter;
	char	*nbr_str;

	counter = 0;
	if (!(flags->precision) && nbr == 0)
	{
		counter += print_width(flags->width, 0, 0);
		return (counter);
	}
	nbr_str = utoa(nbr);
	if (!nbr_str)
		return (0);
	counter += flags_unsigned(nbr_str, flags);
	free(nbr_str);
	return (counter);
}
