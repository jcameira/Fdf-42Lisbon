/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_checks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 13:08:07 by jcameira          #+#    #+#             */
/*   Updated: 2023/11/03 13:08:09 by jcameira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	check_minus(t_pf_flags *flags)
{
	flags->minus = 1;
	flags->zero = 0;
	return ;
}

int	check_precision(const char *str, t_pf_flags *flags, int i)
{
	flags->precision = 0;
	i++;
	while (ft_isdigit(str[i]))
		flags->precision = flags->precision * 10 + (str[i++] - '0');
	return (i);
}

void	check_digit(const char *str, t_pf_flags *flags, int i)
{
	flags->width = flags->width * 10 + (str[i] - '0');
}

int	check_specifier(char str)
{
	if (str == 'c' || str == 's' || str == 'p' || str == 'd' || str == 'i'
		|| str == 'u' || str == 'x' || str == 'X' || str == '%')
		return (1);
	return (0);
}

int	check_flag(char str)
{
	if (str == '-' || str == '0' || str == '.' || str == '#' || str == ' '
		|| str == '+')
		return (1);
	return (check_specifier(str) || ft_isdigit(str));
}
