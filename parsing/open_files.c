/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plbuet <plbuet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 17:27:03 by plbuet            #+#    #+#             */
/*   Updated: 2025/05/16 14:45:07 by plbuet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../include/cub3d.h"

void	extract_texture(char *line, t_texture *texture)
{
	int	i;

	i = 0;
	while(line[i])
	{
		if(ft_strncmp(&line[i], 'F'))
	}
}
int check_file(char *name_files)
{
	int	i;
	char *check;
	i = 0;
	
	check = ft_strrchr(name_files, ".");
	if ((ft_strncmp(check, ".cub", 4)) && ft_strlen(check) == 4)
		return(0);
	return(1);
}
int	openFiles(char *name_files, t_texture texture)
{
	int		fd;
	char	*line;
	int		i;

	i = 0;
	if (!check_file(name_files))
	{
		perror("Error\n incorect name files\n");
		return(1);
	}
	if (!(fd = open(name_files)) == -1)
	{
		perror("Error\n open files failed\n");
		return(1);
	}
	while((line = get_next_line(fd)))
	{
		while(!ft_is_alpha(line[i]))
			i ++;
		if (line[i] != '\n')
			extract_data(line, texture);
	}
	free(line);
}
