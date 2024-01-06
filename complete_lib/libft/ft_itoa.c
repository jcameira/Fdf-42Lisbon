/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 15:12:35 by jcameira          #+#    #+#             */
/*   Updated: 2023/10/07 20:29:26 by jcameira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	num_len(int n)
{
	int		len;
	long	n_tmp;

	len = 0;
	n_tmp = n;
	if (n_tmp == 0)
		return (1);
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

char	*ft_itoa(int n)
{
	int		n_len;
	char	*num;

	n_len = num_len(n);
	num = malloc(sizeof (char) * (n_len + 1));
	if (!num)
		return (NULL);
	if (n == 0)
	{
		num[0] = '0';
		num[1] = '\0';
		return (num);
	}
	if (n < 0)
		num[0] = '-';
	num[n_len] = '\0';
	while (n != 0)
	{
		if ((n % 10) < 0)
			num[n_len-- - 1] = (n % 10) * (-1) + 48;
		else
			num[n_len-- - 1] = (n % 10) + 48;
		n /= 10;
	}
	return (num);
}
