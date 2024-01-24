/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 13:30:27 by jcameira          #+#    #+#             */
/*   Updated: 2024/01/24 00:33:41 by jcameira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	load_coordinates(t_map *map, t_point ***points, char **z_values, int y)
{
	int	x;

	x = -1;
	while (++x < map->limits[X])
	{
		(*points)[y][x].coordinates[X] = (x - (map->limits[X] / 2) + 0.5) * 75;
		(*points)[y][x].coordinates[Y] = (y - (map->limits[Y] / 2) + 0.5) * 75;
		(*points)[y][x].coordinates[Z] = (float)atoi(z_values[x]) * 10;
	}
}

t_point	**get_original_points(t_map *map)
{
	int		i;
	int		y;
	char	**z_values;
	t_point	**points;

	points = malloc(sizeof (t_point *) * map->limits[Y]);
	if (!points)
		return (NULL);
	y = -1;
	while (++y < map->limits[Y])
	{
		points[y] = malloc(sizeof (t_point) * map->limits[X]);
		if (!points[y])
			return (NULL);
		z_values = ft_split(map->map_info[y], ' ');
		if (!z_values)
			return (NULL);
		i = -1;
		while (z_values[++i])
			printf("Z value: %s\n", z_values[i]);
		load_coordinates(map, &points, z_values, y);
	}
	return (points);
}

char	**read_map(t_map *map, char *file)
{
	int		fd;
	int		y;
	char	**map_info;

	map_info = malloc(sizeof (char *) * (map->limits[Y] + 1));
	if (!map_info)
		return (NULL);
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (NULL);
	y = -1;
	map_info[++y] = get_next_line(fd);
	while (map_info[y])
	{
		map_info[y] = ft_strtrim(map_info[y], " \n");
		map_info[++y] = get_next_line(fd);
	}
	close(fd);
	return (map_info);
}

void	get_x_y_limits(t_map *map, char *file)
{
	int		fd;
	char	*line;

	fd = open(file, O_RDONLY);
	line = get_next_line(fd);
	line = ft_strtrim(line, " \n");
	map->limits[X] = (float)word_count(line, ' ');
	map->limits[Y] = 0;
	while (line)
	{
		map->limits[Y]++;
		line = get_next_line(fd);
	}
	free(line);
	printf("X limit: %f\n", map->limits[X]);
	printf("Y limit: %f\n", map->limits[Y]);
	close(fd);
}

void	parser(t_map *map, char *file)
{
	int		i;
	int		j;

	map_init(map);
	get_x_y_limits(map, file);
	map->map_info = read_map(map, file);
	map->points = get_original_points(map);
	i = -1;
	while (++i < map->limits[Y])
	{
		j = -1;
		while (++j < map->limits[X])
		{
			printf("I, J: %d, %d\n", i, j);
			printf("X Y Z: %f %f %f\n", map->points[i][j].coordinates[X], map->points[i][j].coordinates[Y], map->points[i][j].coordinates[Z]);
		}
	}
}
