/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 13:30:27 by jcameira          #+#    #+#             */
/*   Updated: 2024/01/08 21:39:22 by jcameira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_point	**create_initial_points(t_map *map)
{
	int		i;
	int		j;
	char	**z_values;
	t_point	**points;

	points = malloc(sizeof (t_point *) * map->limits[Y]);
	if (!points)
		return (NULL);
	z_values = ft_split(map->map_info, ' ');
	if (!z_values)
		return (NULL);
	i = -1;
	while (++i < map->limits[Y])
	{
		points[i] = malloc(sizeof (t_point));
		if (!point)
			return (NULL);
		points[i]->coordinates[X] = i - map->origin->coordinates[X];
		points[i]->coordinates[Y] = i - map->origin->coordinates[Y];
		points[i]->coordinates[Z] = z_values[i*j];
	}
}

char	*read_map(t_map *map, char *file)
{
	int		fd;
	int		x;
	int		y;
	char	*map_info;
	char	*line;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (NULL);
	line = get_next_line(fd);
	map->limits[X] = word_count(line);
	y = 0
	while (line)
	{
		y++;
		map_info = ft_strjoin(map_info, line);
		line = get_next_line(fd);
	}
	map->limits[Y] = i;
	free(line);
	return (map_info);
}

t_map	*parser(t_vars fdf, char *file)
{
	t_map	*map;

	map = map_init();
	map->map_info = read_map(map, file);
	if (!map->info)
		return (NULL);
	map->points = create_initial_points(map);
}
