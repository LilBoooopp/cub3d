/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbopp <cbopp@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 17:27:03 by plbuet            #+#    #+#             */
/*   Updated: 2025/06/02 23:42:38 by cbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	open_xpm(t_cub *c)
{
	c->north = setup_xpm(c, c->tex.n, set_vec2(626, 417));
	c->east = setup_xpm(c, c->tex.ea, set_vec2(626, 417));
	c->south = setup_xpm(c, c->tex.s, set_vec2(626, 417));
	c->west = setup_xpm(c, c->tex.we, set_vec2(626, 417));
}

void	extract_texture(char *line, t_tex *texture)
{
	int	i;

	i = 0;
	if(line[i] == 'F')
		color(&line[i + 1], 0, texture);
	else if(line[i] == 'C')
		color(&line[i + 1], 1, texture);
	else
		c_point(line, texture);
}
int check_file(char *name_files, char *extension, size_t size, int clos)
{
	char *check;
	int	fd;

	check = ft_strrchr(name_files, '.');
	if ((ft_strncmp(check, extension, size) == 1) || ft_strlen(check) != size)
	{
		printf("wrong extention name : %s\n", name_files);
		return (0);
	}
	if ((fd = open(name_files, O_RDONLY)) == -1)
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

t_map	*openFiles(char *name_files, t_tex *texture)
{
	int		fd;
	char	*line;

	if ((fd = check_file(name_files, ".cub", 4, 0)) == 0)
	{
		perror("Error\n incorect name files\n");
		return (NULL);
	}
	while((line = get_next_line(fd)) && (texture->full < 6 || *line == '\n'))
	{
		if (*line != '\n')
			extract_texture(line, texture);
	}
	if (!check_file(texture->ea, ".xpm", 4, 1) || !check_file(texture->we, ".xpm", 4, 1)||
		!check_file(texture->n, ".xpm", 4, 1) || !check_file(texture->s, ".xpm", 4, 1))
	{
		perror("Error\n incorect name files");
		free (texture);
		return (NULL);
	}
	return (read_map(fd, line));
}

t_map	*ini_map(t_cub *cub, char **v)
{
	t_map		*map;
	t_tex	*texture;

	texture = malloc(sizeof(t_tex));
	if (!texture)
		return (NULL);
	texture->full = 0;
	texture->c[0] = '\0';
	texture->f[0] = '\0';
	texture->n = NULL;
	texture->s = NULL;
	texture->we = NULL;
	texture->ea = NULL;
	map = openFiles(v[1], texture);
	if (!map)
		return (NULL);
	cub->tex = *texture;
	return (map);
}

