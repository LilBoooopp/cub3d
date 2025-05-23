/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbuet <pbuet@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 17:27:03 by plbuet            #+#    #+#             */
/*   Updated: 2025/05/22 14:29:52 by pbuet            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	extract_texture(char *line, t_texture *texture)
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
int check_file(char *name_files)
{
	char *check;
	
	check = ft_strrchr(name_files, '.');
	if ((ft_strncmp(check, ".cub", 4) == 0) && ft_strlen(check) == 4)
		return (0);
	return (1);
}

t_map	*openFiles(char *name_files, t_texture *texture)
{
	int		fd;
	char	*line;
	t_map	*map;

	if (check_file(name_files) == 1)
	{
		perror("Error\n incorect name files\n");
		return (NULL);
	}
	if ((fd = open(name_files, O_RDONLY)) == -1)
		return (NULL);
	map = malloc(sizeof(t_map));
	if (!map)
		return (NULL);
	while((line = get_next_line(fd)) && (texture->full < 6 || *line == '\n'))
	{
		if (*line != '\n')
			extract_texture(line, texture);
	}
	return (read_map(fd, line));
}

t_map	*ini_map(t_cub *cub, char **v)
{
	t_map		*map;
	t_texture	texture;

	texture.full = 0;
	texture.c[0] = '\0';
	texture.f[0] = '\0';
	texture.n = NULL;
	texture.s = NULL;
	texture.we = NULL;
	texture.ea = NULL;
	map = openFiles(v[1], &texture);
	if (!map)
		return (NULL);
	cub->texture =  texture;
	return (map);
}

