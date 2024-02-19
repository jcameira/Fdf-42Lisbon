/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 22:11:27 by jcameira          #+#    #+#             */
/*   Updated: 2023/11/02 18:53:06 by jcameira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_hashtag(int uppercase, t_pf_flags *flags)
{
	if (uppercase)
		write_str("0X", flags);
	else
		write_str("0x", flags);
	return (2);
}

int	write_hex(char *nbr_str, unsigned int nbr, int uppercase, t_pf_flags *flags)
{
	int	count;

	count = 0;
	if (!(flags->zero) && flags->hashtag && nbr > 0)
		count += print_hashtag(uppercase, flags);
	if (flags->precision >= 0)
		count += print_width(flags->precision, ft_strlen(nbr_str), 1);
	count += write_str(nbr_str, flags);
	return (count);
}

int	flags_hex(char *nbr_str, unsigned int nbr, int uppercase, t_pf_flags *flags)
{
	int	counter;

	counter = 0;
	if (flags->precision >= 0 && (size_t)flags->precision < ft_strlen(nbr_str))
		flags->precision = ft_strlen(nbr_str);
	if (flags->zero && flags->hashtag && nbr > 0)
		counter += print_hashtag(uppercase, flags);
	if (flags->minus)
		counter += write_hex(nbr_str, nbr, uppercase, flags);
	if (flags->precision >= 0)
	{
		flags->width -= flags->precision;
		counter += print_width(flags->width, 0, 0);
	}
	else
		counter += print_width(flags->width,
				ft_strlen(nbr_str) + (flags->hashtag * 2), flags->zero);
	if (flags->minus == 0)
		counter += write_hex(nbr_str, nbr, uppercase, flags);
	return (counter);
}

int	print_hex(unsigned int nbr, int uppercase, t_pf_flags *flags)
{
	char	*nbr_str;
	int		counter;

	counter = 0;
	if (!(flags->precision) && nbr == 0)
	{
		counter += print_width(flags->width, 0, 0);
		return (counter);
	}
	nbr_str = xtoa(nbr, uppercase);
	if (!nbr_str)
		return (0);
	counter += flags_hex(nbr_str, nbr, uppercase, flags);
	free(nbr_str);
	return (counter);
}
