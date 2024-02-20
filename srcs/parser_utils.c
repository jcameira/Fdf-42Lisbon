/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 12:33:36 by jcameira          #+#    #+#             */
/*   Updated: 2024/02/20 10:24:27 by jcameira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	print_progress_bar(int progress, int total, char *map_name)
{
	int	length;
	int	i;

	length = progress * 50 / total;
	ft_printf("%s [", map_name);
	i = -1;
	while (++i < 50)
	{
		if (i < length)
			ft_printf("#");
		else
			ft_printf("-");
	}
	ft_printf("] %d%%\r", progress * 100 / total);
}

int	fd_check(int *fd, char *file)
{
	*fd = open(file, O_RDONLY);
	if (*fd < 0)
	{
		ft_printf(ERROR_OPEN, file);
		return (1);
	}
	if (read(*fd, 0, 0) < 0)
	{
		ft_printf(ERROR_READ, file);
		close(*fd);
		return (1);
	}
	return (0);
}

void	*malloc_map_error(int fd, char *file)
{
	ft_printf(ERROR_MAP_INFO, file);
	close(fd);
	return (NULL);
}

void	*malloc_points_error(char *file)
{
	ft_printf(ERROR_LOAD, file);
	return (NULL);
}

void	*exit_read_map_early(char **map_info, int fd, char *file)
{
	int	i;

	i = -1;
	while (map_info[++i])
		free(map_info[i]);
	free(map_info);
	return (malloc_map_error(fd, file));
}
