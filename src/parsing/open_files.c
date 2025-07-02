/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbuet <pbuet@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 17:27:03 by plbuet            #+#    #+#             */
/*   Updated: 2025/07/02 21:09:59 by pbuet            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	open_xpm(t_cub *c)
{
	int	error;

	error = 0;
	error = setup_xpm(c, &c->north, c->tex.n);
	error = setup_xpm(c, &c->east, c->tex.ea);
	error = setup_xpm(c, &c->south, c->tex.s);
	error = setup_xpm(c, &c->west, c->tex.we);
	error = setup_xpm(c, &c->doors, c->tex.door);
	return (error);
}

void	extract_texture(char *line, t_tex *texture)
{
	char	*tmp;
	int		i;

	i = 2;
	while (line[i] && line[i] == ' ')
		i ++;
	tmp = ft_strtrim(&line[i], "\n");
	if (line[0] == 'F' && !texture->f && line[1] == ' ')
	{
		texture->f = ft_strdup(tmp);
		texture->full++;
	}
	else if (line[0] == 'C' && !texture->c && line[1] == ' ')
	{
		texture->c = ft_strdup(tmp);
		texture->full++;
	}
	else
		c_point(texture, tmp, line);
	free(tmp);
}

int	check_file(char *name_files, char *extension, size_t size, int clos)
{
	char	*check;
	int		fd;

	check = ft_strrchr(name_files, '.');
	if ((ft_strncmp(check, extension, size) == 1) || ft_strlen(check) != size)
	{
		error_msg("Wrong extention name");
		return (-1);
	}
	fd = open(name_files, O_RDWR);
	if (fd == -1)
		return (error_msg("Open failed"), -1);
	if (clos == 1)
		return (close(fd), 1);
	return (fd);
}

t_map	*openfiles(char *name_files, t_tex *texture)
{
	int		fd;
	char	*line;
	char	*temp;

	fd = check_file(name_files, ".cub", 4, 0);
	if (fd == -1)
		return (NULL);
	line = get_next_line(fd);
	while (line && (texture->full < 6 || *line == '\n'))
	{
		if (*line != '\n')
			extract_texture(line, texture);
		free(line);
		line = get_next_line(fd);
	}
	temp = line;
	if (texture->full != 6)
	{
		error_msg("Texture error\n");
		return (NULL);
	}
	if (texture_check(texture, fd, temp))
		return (NULL);
	return (read_map(fd, temp, 0, 0));
}

t_map	*ini_map(t_cub *cub, char **v)
{
	t_map		*map;
	t_tex		*texture;
	int			y;

	texture = malloc(sizeof(t_tex));
	if (!texture)
		return (NULL);
	ini_texture(texture);
	map = openfiles(v[1], texture);
	cub->tex = *texture;
	free(texture);
	cub->tex.door = ft_strdup("resources/vault.xpm");
	if (!map || !check_file(cub->tex.door, ".xpm", 4, 1))
		return (free_texture(cub), NULL);
	search_player(map, 1);
	map->explored = malloc(sizeof(bool *) * map->sizey);
	y = -1;
	while (++y < map->sizey)
		map->explored[y] = ft_calloc(map->sizex, sizeof(bool));
	return (map);
}
