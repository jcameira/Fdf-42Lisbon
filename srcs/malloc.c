/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 00:45:31 by jcameira          #+#    #+#             */
/*   Updated: 2024/02/20 00:45:32 by jcameira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <time.h>
#include <stdlib.h>

extern void	*__real_malloc(size_t size);

void	*__wrap_malloc(size_t size)
{
	srand(time(NULL));
	if (rand() % 2)
		return (NULL);
	return (__real_malloc(size));
}
