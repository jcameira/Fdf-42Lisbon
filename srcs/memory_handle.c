/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_handle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 16:23:16 by jcameira          #+#    #+#             */
/*   Updated: 2024/02/17 00:14:26 by jcameira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	free_split(char **split)
{
	int	i;

	i = -1;
	while (split[++i])
		free(split[i]);
	free(split);
}

void	free_map(t_map *map)
{
	int	y;

	y = -1;
	while (++y < map->lim[Y])
	{
		free(map->points[y]);
		free(map->map_info[y]);
	}
	free(map->points);
	free(map->map_info);
}

void	free_proj(t_point **proj, t_map map)
{
	int	y;

	y = -1;
	while (++y < map.lim[Y])
		free(proj[y]);
	free(proj);
}
