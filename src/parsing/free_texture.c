/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbopp <cbopp@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 19:23:19 by pbuet             #+#    #+#             */
/*   Updated: 2025/08/20 17:36:00 by cbopp            ###   ########.fr       */
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
	close(fd);
}

int	rgb_check(t_tex *texture)
{
	int	r;
	int	g;
	int	b;

	r = 0;
	g = 0;
	b = 0;
	if (ft_isalphastr(texture->c))
		return (1);
	if (ft_isalphastr(texture->f))
		return (1);
	if (parse_rgbint(texture->c, &r, &g, &b))
		return (1);
	if ((r > 255 || r < 0)
		|| (g > 255 || g < 0)
		|| (b > 255 || b < 0))
		return (1);
	if (parse_rgbint(texture->f, &r, &g, &b))
		return (1);
	if ((r > 255 || r < 0)
		|| (g > 255 || g < 0)
		|| (b > 255 || b < 0))
		return (1);
	return (0);
}

int	texture_check(t_tex *texture, int fd, char *temp)
{
	if (check_file(texture->ea, ".xpm", 4, 1) == -1
		||check_file(texture->we, ".xpm", 4, 1) == -1
		||check_file(texture->n, ".xpm", 4, 1) == -1
		||check_file(texture->s, ".xpm", 4, 1) == -1)
	{
		close_gnl(temp, fd);
		return (1);
	}
	if (rgb_check(texture))
	{
		error_msg("RGB values can only be 0-255");
		close_gnl(temp, fd);
		return (1);
	}
	return (0);
}

int	checkline(char *line)
{
	if (!line)
	{
		error_msg("empty map");
		return (1);
	}
	return(0);
}
