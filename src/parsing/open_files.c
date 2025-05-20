/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbopp <cbopp@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 17:27:03 by plbuet            #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/05/19 19:53:46 by plbuet           ###   ########.fr       */
=======
/*   Updated: 2025/05/19 18:59:31 by cbopp            ###   ########.fr       */
>>>>>>> main
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
		return(0);
	return(1);
}

t_map	*openFiles(char *name_files, t_texture *texture)
{
	int		fd;
	char	*line;
	t_map	*map;

	if (check_file(name_files) == 1)
	{
		perror("Error\n incorect name files\n");
		return(NULL);
	}
	if ((fd = open(name_files, O_RDONLY)) == -1) // fonction checkant l'ouverture du fichier
		return(NULL);
	map = malloc(sizeof(t_map));
	if (!map)
		return(NULL);
	while((line = get_next_line(fd)) && (texture->full < 6 || *line == '\n'))
	{
		if (*line != '\n')
			extract_texture(line, texture);
	}
	printf("%s\n%s\n%s\n%s\n%d\n",texture->n, texture->s, texture->we, texture->ea, texture->full);
	return (read_map(fd, line));
}

t_map	*ini_map(t_cub *cub, char **v)
{
	t_map		*map;
	t_texture	texture;
	int			i;
	
	i = 0;
	texture.full = 0;
	texture.c[0] = '\0';
	texture.f[0] = '\0';
	texture.n = NULL;
	texture.s = NULL;
	texture.we = NULL;
	texture.ea = NULL;
	map = openFiles(v[1], &texture);
	if (!map)
		return(NULL);
	while (i < map->sizey)
	{
		printf("%s\n", map->map[i]);
		i ++;
	}
	cub->texture =  texture;
	printf("%s\n%s\n%s\n%s\n",texture.n, texture.s, texture.we, texture.ea);
	printf("%s\n%s\n", texture.c, texture.f);
	return(map);
}

