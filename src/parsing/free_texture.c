/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbuet <pbuet@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 19:23:19 by pbuet             #+#    #+#             */
/*   Updated: 2025/07/02 17:40:51 by pbuet            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	free_texture(t_cub *c)
{
	if (c->tex.we)
		free(c->tex.we);
	if (c->tex.n)
		free(c->tex.n);
	if (c->tex.s)
		free(c->tex.s);
	if (c->tex.ea)
		free(c->tex.ea);
	if (c->tex.door)
		free(c->tex.door);
	if (c->tex.f)
		free(c->tex.f);
	if (c->tex.c)
		free(c->tex.c);
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

int	rgb_check(t_tex *texture)
{
	int	r;
	int	g;
	int	b;

	parse_rgbint(texture->c, &r, &g, &b);
	if ((r > 255 || r < 0)
		|| (g > 255 || g < 0)
		|| (b > 255 || b < 0))
		return (1);
	parse_rgbint(texture->f, &r, &g, &b);
	if ((r > 255 || r < 0)
		|| (g > 255 || g < 0)
		|| (b > 255 || b < 0))
		return (1);
	return (0);
}

int	texture_check(t_tex *texture, int fd, char *temp)
{
	if (!check_file(texture->ea, ".xpm", 4, 1)
		||!check_file(texture->we, ".xpm", 4, 1)
		||!check_file(texture->n, ".xpm", 4, 1)
		||!check_file(texture->s, ".xpm", 4, 1)
		|| rgb_check(texture))
	{
		perror("Error\n incorect name files");
		close_gnl(temp, fd);
		return (1);
	}
	return (0);
}
