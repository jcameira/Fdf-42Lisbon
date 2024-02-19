/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 17:38:49 by jcameira          #+#    #+#             */
/*   Updated: 2023/11/21 12:21:26 by jcameira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include "../libft/libft.h"

# define HEX_UPPER "0123456789ABCDEF"
# define HEX_LOWER "0123456789abcdef"

typedef struct s_pf_flags
{
	int	width;
	int	precision;
	int	minus;
	int	zero;
	int	hashtag;
	int	space;
	int	plus;
	int	specifier;
}	t_pf_flags;

int			ft_printf(const char *str, ...);
int			get_arg(char c, va_list args, t_pf_flags *flags);
int			print_char(char c, t_pf_flags *flags);
int			write_char(char c);
int			print_str(const char *str, t_pf_flags *flags);
int			write_str(const char *str, t_pf_flags *flags);
void		check_minus(t_pf_flags *flags);
int			check_precision(const char *str, t_pf_flags *flags, int i);
void		check_digit(const char *str, t_pf_flags *flags, int i);
int			check_specifier(char str);
int			check_flag(char str);
int			check_flags(const char *str, t_pf_flags *flags, int i);
int			print_width(int total_width, int size, int zero);
int			check_sign(int nbr, t_pf_flags *flags);
t_pf_flags	flags_init(void);
int			format_input(const char *str, va_list args);
int			write_nbr(char *num_str, int nbr, t_pf_flags *flags);
int			flags_nbr(char *num_str, int nbr, t_pf_flags *flags);
int			print_nbr(int nbr, t_pf_flags *flags);
char		*long_itoa(long n);
int			num_len(long n);
int			print_hashtag(int uppercase, t_pf_flags *flags);
int			write_hex(char *nbr_str, unsigned int nbr,
				int uppercase, t_pf_flags *flags);
int			print_hex(unsigned int nbr, int uppercase, t_pf_flags *flags);
char		*xtoa(unsigned int nbr, int uppercase);
int			hex_len(unsigned int num);
int			print_unsigned(unsigned int nbr, t_pf_flags *flags);
char		*utoa(unsigned int nbr);
int			print_ptr(unsigned long int nbr, t_pf_flags *flags);
int			write_ptr(char	*nbr_str, unsigned long int nbr, t_pf_flags *flags);
char		*long_xtoa(unsigned long int nbr, int uppercase);
int			long_hex_len(unsigned long int nbr);

#endif