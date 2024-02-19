/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 19:50:27 by jcameira          #+#    #+#             */
/*   Updated: 2023/10/29 19:06:37 by jcameira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	write_str(const char *str, t_pf_flags *flags)
{
	int	i;

	i = 0;
	if (flags->precision >= 0)
		while (str[i] && i < flags->precision)
			ft_putchar_fd(str[i++], 1);
	else
		while (str[i])
			ft_putchar_fd(str[i++], 1);
	return (i);
}

int	print_str(const char *str, t_pf_flags *flags)
{
	int	counter;

	counter = 0;
	if (!str && flags->precision >= 0 && flags->precision < 6)
	{
		counter += print_width(flags->width, 0, 0);
		return (counter);
	}
	if (!str)
		str = "(null)";
	if ((size_t)flags->precision > ft_strlen(str))
		flags->precision = ft_strlen(str);
	if (flags->minus)
		counter += write_str(str, flags);
	flags->zero = 0;
	if (flags->precision >= 0)
		counter += print_width(flags->width, flags->precision, 0);
	else
		counter += print_width(flags->width, ft_strlen(str), 0);
	if (!(flags->minus))
		counter += write_str(str, flags);
	return (counter);
}
