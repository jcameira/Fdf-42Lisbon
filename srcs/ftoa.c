/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftoa.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 00:56:38 by jcameira          #+#    #+#             */
/*   Updated: 2024/02/13 20:00:16 by jcameira         ###   ########.fr       */
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

static void	add_int(float n, char *buffer, int precision, int length)
{
	int	tmp_int;

	tmp_int = (int)n;
	if (tmp_int == 0)
	{
		if (n < 0)
		{
			buffer[0] = '-';
			buffer[1] = '0';
		}
		else
			buffer[0] = '0';
	}
	while (tmp_int != 0)
	{
		if ((tmp_int % 10) < 0)
			buffer[length-- - 2 - precision] = (tmp_int % 10) * (-1) + '0';
		else
			buffer[length-- - 2 - precision] = (tmp_int % 10) + '0';
		tmp_int /= 10;
	}
}

static void	add_dec(float n, char *buffer, int precision, int length)
{
	float	tmp_float;

	tmp_float = n - (int)n;
	while (precision > 0)
	{
		tmp_float *= 10;
		if (((int)tmp_float % 10) < 0)
			buffer[length - precision] = ((int)tmp_float % 10) * (-1) + '0';
		else
			buffer[length - precision] = ((int)tmp_float % 10) + '0';
		tmp_float -= (int)tmp_float;
		precision--;
	}
}

char	*ftoa(float n, int precision)
{
	int		n_len;
	char	*buffer;

	n_len = fnum_len(n, precision);
	buffer = malloc(sizeof(char) * (n_len + 1));
	if (!buffer)
		return (NULL);
	buffer[n_len] = '\0';
	if (precision > 0)
		buffer[n_len - 1 - precision] = '.';
	if (n == 0)
	{
		buffer[0] = '0';
		while (precision > 0)
		{
			buffer[2 + precision] = '0';
			precision--;
		}
		return (buffer);
	}
	if (n < 0)
		buffer[0] = '-';
	add_int(n, buffer, precision, n_len);
	add_dec(n, buffer, precision, n_len);
	return (buffer);
}
