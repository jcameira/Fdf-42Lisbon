/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_handle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 16:23:16 by jcameira          #+#    #+#             */
/*   Updated: 2024/02/01 16:27:39 by jcameira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	free_projection(t_point **projection, t_map map)
{
	int	y;

	y = -1;
	while (++y < map.limits[Y])
		free(projection[y]);
	free(projection);
}