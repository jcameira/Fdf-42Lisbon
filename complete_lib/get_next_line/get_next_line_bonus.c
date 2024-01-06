/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 01:48:12 by jcameira          #+#    #+#             */
/*   Updated: 2023/11/21 02:35:57 by jcameira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*get_next_line(int fd)
{
	int			flag;
	int			flag2;
	char		*line;
	static char	buffer[FOPEN_MAX][BUFFER_SIZE + 1];

	flag = 0;
	flag2 = 0;
	if (fd < 0 || read(fd, 0, 0) < 0 || BUFFER_SIZE < 1)
	{
		if (fd >= 0 && fd <= FOPEN_MAX)
			ft_remove_last_line(buffer[fd], &flag, &flag2);
		return (NULL);
	}
	line = NULL;
	flag2 = 1;
	while (!flag && (*buffer[fd] != 0 || read(fd, buffer[fd], BUFFER_SIZE) > 0))
	{
		line = ft_strjoin_gnl(line, buffer[fd]);
		ft_remove_last_line(buffer[fd], &flag, &flag2);
	}
	return (line);
}
