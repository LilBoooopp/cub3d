/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbuet <pbuet@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 19:23:19 by pbuet             #+#    #+#             */
/*   Updated: 2025/06/20 14:09:03 by pbuet            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"parsing.h"

void	free_texture(t_cub *c)
{
	free(c->tex.we);
	free(c->tex.n);
	free(c->tex.s);
	free(c->tex.ea);
}

void	close_gnl(char *line, int fd)
{
	free(line);
	line = get_next_line(fd);
	while (line)
	{
		free(line);
		line = get_next_line(fd);
	}
	free(line);
}

int	texture_check(t_tex *texture, int fd, char *temp)
{
	if (!check_file(texture->ea, ".xpm", 4, 1)
		||!check_file(texture->we, ".xpm", 4, 1)
		||!check_file(texture->n, ".xpm", 4, 1)
		||!check_file(texture->s, ".xpm", 4, 1))
	{
		perror("Error\n incorect name files");
		close_gnl(temp, fd);
		return (1);
	}
	return (0);
}
