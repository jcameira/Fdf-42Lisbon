/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ftoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 00:56:38 by jcameira          #+#    #+#             */
/*   Updated: 2024/02/19 17:35:51 by jcameira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	fnum_len(float n, int precision)
{
	int		len;
	long	n_tmp;

	len = 0;
	n_tmp = (long)n;
	if (precision > 0)
		len += 1 + precision;
	if (n_tmp == 0)
	{
		if (n < 0)
			return (len + 2);
		return (len + 1);
	}
	if (n_tmp < 0)
	{
		n_tmp *= -1;
		len++;
	}
	while (n_tmp > 0)
	{
		n_tmp /= 10;
		len++;
	}
	return (len);
}

static void	add_int(float n, char *n_str, int precision, int length)
{
	int	tmp_int;

	tmp_int = (int)n;
	if (tmp_int == 0)
	{
		if (n < 0)
		{
			n_str[0] = '-';
			n_str[1] = '0';
		}
		else
			n_str[0] = '0';
	}
	while (tmp_int != 0)
	{
		if ((tmp_int % 10) < 0 && precision > 0)
			n_str[length-- - 2 - precision] = (tmp_int % 10) * (-1) + '0';
		else if ((tmp_int % 10) < 0)
			n_str[length-- - 1] = (tmp_int % 10) * (-1) + '0';
		else if ((tmp_int % 10) >= 0 && precision > 0)
			n_str[length-- - 2 - precision] = (tmp_int % 10) + '0';
		else if ((tmp_int % 10) >= 0)
			n_str[length-- - 1] = (tmp_int % 10) + '0';
		tmp_int /= 10;
	}
}

static void	add_dec(float n, char *n_str, int precision, int length)
{
	float	tmp_float;

	tmp_float = n - (int)n;
	while (precision > 0)
	{
		tmp_float *= 10;
		if (((int)tmp_float % 10) < 0)
			n_str[length - precision] = ((int)tmp_float % 10) * (-1) + '0';
		else
			n_str[length - precision] = ((int)tmp_float % 10) + '0';
		tmp_float -= (int)tmp_float;
		precision--;
	}
}

char	*ft_ftoa(float n, int precision)
{
	int		n_len;
	char	*n_str;

	n_len = fnum_len(n, precision);
	n_str = malloc(sizeof(char) * (n_len + 1));
	if (!n_str)
		return (NULL);
	n_str[n_len] = '\0';
	if (precision > 0)
		n_str[n_len - 1 - precision] = '.';
	if (n == 0)
	{
		n_str[0] = '0';
		while (precision > 0)
		{
			n_str[1 + precision] = '0';
			precision--;
		}
		return (n_str);
	}
	if (n < 0)
		n_str[0] = '-';
	add_int(n, n_str, precision, n_len);
	add_dec(n, n_str, precision, n_len);
	return (n_str);
}
