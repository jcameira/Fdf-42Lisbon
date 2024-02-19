/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 13:08:14 by jcameira          #+#    #+#             */
/*   Updated: 2023/11/03 13:08:16 by jcameira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_width(int total_width, int size, int zero)
{
	int	counter;

	counter = 0;
	while (total_width - size > 0)
	{
		if (zero)
			ft_putchar_fd('0', 1);
		else
			ft_putchar_fd(' ', 1);
		total_width--;
		counter++;
	}
	return (counter);
}

int	check_sign(int nbr, t_pf_flags *flags)
{
	int	counter;

	counter = 0;
	if (nbr < 0 && flags->precision < 0)
	{
		ft_putchar_fd('-', 1);
		counter++;
	}
	else if (flags->plus)
	{
		ft_putchar_fd('+', 1);
		counter++;
	}
	else if (flags->space)
	{
		ft_putchar_fd(' ', 1);
		counter++;
		flags->width--;
	}
	return (counter);
}
