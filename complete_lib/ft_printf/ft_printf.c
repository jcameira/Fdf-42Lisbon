/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 17:38:46 by jcameira          #+#    #+#             */
/*   Updated: 2023/11/03 13:03:43 by jcameira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_pf_flags	flags_init(void)
{
	t_pf_flags	flags;

	flags.width = 0;
	flags.precision = -1;
	flags.minus = 0;
	flags.zero = 0;
	flags.hashtag = 0;
	flags.space = 0;
	flags.plus = 0;
	flags.specifier = 0;
	return (flags);
}

int	check_flags(const char *str, t_pf_flags *flags, int i)
{
	while (str[++i] && check_flag(str[i]))
	{
		if (str[i] == '-')
			check_minus(flags);
		if (str[i] == '0' && flags->minus == 0 && flags->width == 0)
			flags->zero = 1;
		if (str[i] == '.')
			i = check_precision(str, flags, i);
		if (str[i] == '#')
			flags->hashtag = 1;
		if (str[i] == ' ')
			flags->space = 1;
		if (str[i] == '+')
			flags->plus = 1;
		if (ft_isdigit(str[i]))
			check_digit(str, flags, i);
		if (check_specifier(str[i]))
		{
			flags->specifier = str[i];
			break ;
		}
	}
	return (i);
}

int	get_arg(char c, va_list args, t_pf_flags *flags)
{
	int	counter;

	counter = 0;
	if (c == '%')
	{
		write(1, "%", 1);
		counter++;
	}
	else if (c == 'c')
		counter += print_char(va_arg(args, int), flags);
	else if (c == 's')
		counter += print_str(va_arg(args, const char *), flags);
	else if (c == 'd' || c == 'i')
		counter += print_nbr(va_arg(args, int), flags);
	else if (c == 'x')
		counter += print_hex(va_arg(args, unsigned int), 0, flags);
	else if (c == 'X')
		counter += print_hex(va_arg(args, unsigned int), 1, flags);
	else if (c == 'u')
		counter += print_unsigned(va_arg(args, unsigned int), flags);
	else if (c == 'p')
		counter += print_ptr(va_arg(args, unsigned long int), flags);
	return (counter);
}

int	format_input(const char *str, va_list args)
{
	int			i;
	int			tmp_i;
	int			counter;
	t_pf_flags	flags;

	i = 0;
	counter = 0;
	while (str[i])
	{
		flags = flags_init();
		if (str[i] == '%' && str[i + 1] != '\0')
		{
			tmp_i = check_flags(str, &flags, i);
			if (flags.specifier > 0)
				i = tmp_i;
			if (str[i] != '\0' && flags.specifier > 0 && check_flag(str[i]))
				counter += get_arg(str[i], args, &flags);
			else if (str[i] != '\0')
				counter += write_char(str[i]);
		}
		else
			counter += write_char(str[i]);
		i++;
	}
	return (counter);
}

int	ft_printf(const char *str, ...)
{
	va_list		args;
	int			counter;

	if (!str || *str == '\0')
		return (0);
	va_start(args, str);
	counter = format_input(str, args);
	va_end(args);
	return (counter);
}
