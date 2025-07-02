/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbuet <pbuet@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 17:27:03 by plbuet            #+#    #+#             */
/*   Updated: 2025/07/02 17:36:34 by pbuet            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	open_xpm(t_cub *c)
{
	c->north = setup_xpm(c, c->tex.n);
	c->east = setup_xpm(c, c->tex.ea);
	c->south = setup_xpm(c, c->tex.s);
	c->west = setup_xpm(c, c->tex.we);
	c->doors = setup_xpm(c, c->tex.door);
}

void	extract_texture(char *line, t_tex *texture)
{
	char	*tmp;

	tmp = ft_strtrim(line, "\n");
	if (line[0] == 'F' && !texture->f && line[1] == ' ')
	{
		texture->f = ft_strdup(&tmp[2]);
		texture->full++;
	}
	else if (line[0] == 'C' && !texture->c && line[1] == ' ')
	{
		texture->c = ft_strdup(&tmp[2]);
		texture->full++;
	}
	else
		c_point(texture, tmp);
	free(tmp);
}

int	check_file(char *name_files, char *extension, size_t size, int clos)
{
	char	*check;
	int		fd;

	check = ft_strrchr(name_files, '.');
	if ((ft_strncmp(check, extension, size) == 1) || ft_strlen(check) != size)
	{
		printf("wrong extention name : %s\n", name_files);
		return (0);
	}
	fd = open(name_files, O_RDONLY);
	if (fd == -1)
	{
		printf("open failed for : %s\n", name_files);
		return (0);
	}
	if (clos == 1)
	{
		close(fd);
		return (1);
	}
	return (fd);
}

t_map	*openfiles(char *name_files, t_tex *texture)
{
	int		fd;
	char	*line;
	char	*temp;

	fd = check_file(name_files, ".cub", 4, 0);
	if (fd == 0)
	{
		perror("Error\n incorect name files\n");
		return (NULL);
	}
	line = get_next_line(fd);
	while (line && (texture->full < 6 || *line == '\n'))
	{
		if (*line != '\n')
			extract_texture(line, texture);
		free(line);
		line = get_next_line(fd);
	}
	temp = line;
	if (texture->full != 6 || texture_check(texture, fd, temp))
	{
		printf("erreur texture\n");
		return (NULL);
	}
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
	{
		free_texture(cub);
		return (NULL);
	}
	search_player(map, 1);
	map->explored = malloc(sizeof(bool *) * map->sizey);
	y = -1;
	while (++y < map->sizey)
		map->explored[y] = ft_calloc(map->sizex, sizeof(bool));
	return (map);
}
