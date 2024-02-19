/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_char.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 19:50:45 by jcameira          #+#    #+#             */
/*   Updated: 2023/10/29 19:05:05 by jcameira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	write_char(char c)
{
	ft_putchar_fd(c, 1);
	return (1);
}

int	print_char(char c, t_pf_flags *flags)
{
	int	i;

	i = 0;
	if (flags->minus)
		i += write_char(c);
	i += print_width(flags->width, 1, flags->zero);
	if (!(flags->minus))
		i += write_char(c);
	return (i);
}
