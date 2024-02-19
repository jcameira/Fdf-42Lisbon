/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_nbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 01:24:31 by jcameira          #+#    #+#             */
/*   Updated: 2023/11/03 13:04:31 by jcameira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	write_nbr(char *num_str, int nbr, t_pf_flags *flags)
{
	int	counter;

	counter = 0;
	if (nbr < 0)
	{
		if (!(flags->zero) || flags->precision >= 0)
			counter += write_char('-');
	}
	else if (flags->plus && !(flags->zero))
	{
		counter += write_char('+');
	}
	else if (flags->space && !(flags->zero))
	{
		counter += write_char(' ');
		flags->width--;
	}
	if (flags->precision >= 0)
		counter += print_width(flags->precision, ft_strlen(num_str), 1);
	counter += write_str(num_str, flags);
	return (counter);
}

int	flags_nbr(char *num_str, int nbr, t_pf_flags *flags)
{
	int	counter;

	counter = 0;
	if (flags->precision >= 0 && (size_t)flags->precision < ft_strlen(num_str))
		flags->precision = ft_strlen(num_str);
	if (flags->zero)
		counter += check_sign(nbr, flags);
	if (flags->minus)
		counter += write_nbr(num_str, nbr, flags);
	if (flags->precision >= 0)
	{
		flags->width -= flags->precision;
		counter += print_width(flags->width, 0, 0);
	}
	else
	{
		if (nbr < 0 && flags->plus)
			flags->width++;
		counter += print_width(flags->width - flags->plus,
				ft_strlen(num_str), flags->zero);
	}
	if (!(flags->minus))
		counter += write_nbr(num_str, nbr, flags);
	return (counter);
}

int	print_nbr(int nbr, t_pf_flags *flags)
{
	int		counter;
	long	num;
	char	*num_str;

	num = nbr;
	counter = 0;
	if (num < 0)
	{
		num = -num;
		flags->width--;
	}
	if (!(flags->precision) && nbr == 0)
	{
		counter += print_width(flags->width, 0, 0);
		return (counter);
	}
	num_str = long_itoa(num);
	if (!num_str)
		return (0);
	counter += flags_nbr(num_str, nbr, flags);
	free(num_str);
	return (counter);
}
