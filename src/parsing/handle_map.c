/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plbuet <plbuet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 20:11:33 by plbuet            #+#    #+#             */
/*   Updated: 2025/05/20 13:15:25 by plbuet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"parsing.h"

int	check_map(t_map *map)
{
	int	i = 0;
	int	j = 0;

	while (i < map->sizey)
	{
		j = 0;
		while (j < map->sizex)
		{
			if (map->map[i][j] == 'N' || map->map[i][j] == 'S' || map->map[i][j] == 'E' || map->map[i][j] == 'W')
			{
				map->player_x = j;
				map->player_y = i;
				map->orientation = map->map[i][j];
			}
			else if (map->map[i][j] == ' ' || map->map[i][j] == '1' || map->map[i][j] == '0')
				continue;
			else
				return (1);
		}
		i ++;
	}
	return (0);
}

t_map *tab_map(t_node *lst_map, int max_width)
{
	int		i;
	int		size;
	int		len;
	t_map	*map;

	size = ft_size(lst_map);
	map = malloc(sizeof(t_map));
	map->map = malloc(sizeof(char *) * (size + 1));
	if (!map->map)
		return(NULL);
	map->sizex = size;
	i = 0;
	while (i < size)
	{
		map->map[i] = malloc(sizeof(char) * (max_width + 1));
		len = ft_strlen(lst_map->content);
		ft_memcpy(map->map[i], lst_map->content, len);
		ft_memset(map->map[i] + (len - 1), 32, max_width - len);
		map->map[i][max_width - 1] = '\0';
		lst_map = lst_map->next;
		i ++;
	}
	map->sizex = max_width;
	check_map(map);
	return(map);
}

t_map *read_map(int fd, char *line)
{
	int		max_width;
	int		len;
	t_node *map_list;
	t_node *new;
	t_node *last;

	printf("read map \n");
	map_list = ft_new(line);
	last = map_list;
	max_width = 0;
	while((line = get_next_line(fd)))
	{
		if ((len = ft_strlen(line)) > max_width)
			max_width = len;
		new = ft_new(line);
		if (!new)
			return(NULL);
		last->next = new;
		last = new;
	}
	close(fd);
	free (line);
	return (tab_map(map_list, max_width));
}

