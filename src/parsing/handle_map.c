/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plbuet <plbuet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 20:11:33 by plbuet            #+#    #+#             */
/*   Updated: 2025/05/20 15:20:49 by plbuet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"parsing.h"

void flood_fill_masked(char **map, int x, int y, int width, int height, char **mask)
{
	if (x < 0 || y < 0 || x >= width || y >= height)
		return;
	char c = map[y][x];
	if (c == ' ' || c == '\0' || c == '1' || mask[y][x] == 'x')
		return;

	mask[y][x] = 'x'; // accessible

	flood_fill_masked(map, x + 1, y, width, height, mask);
	flood_fill_masked(map, x - 1, y, width, height, mask);
	flood_fill_masked(map, x, y + 1, width, height, mask);
	flood_fill_masked(map, x, y - 1, width, height, mask);
}

char **build_filtered_map(char **original, char **mask, int height, int width)
{
	char **filtered = malloc(sizeof(char *) * (height + 1));
	for (int y = 0; y < height; y++)
	{
		filtered[y] = malloc(width + 1);
		for (int x = 0; x < width; x++)
		{
			if (mask[y][x] == 'x' || original[y][x] == '1')
				filtered[y][x] = original[y][x]; // zone visitée ou mur
			else
				filtered[y][x] = ' ';
		}
		filtered[y][width] = '\0';
	}
	filtered[height] = NULL;
	return filtered;
}

int	check_map_flood(t_map *map)
{
	int width = ft_strlen(map->map[0]);
	int height = 0;

	while (map->map[height])
		height++;
	int start_x = -1, start_y = -1;
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; map->map[y][x]; x++)
		{
			if (ft_strchr("NSEW", map->map[y][x]))
			{
				start_x = x;
				start_y = y;
				break;
			}
		}
	}
	if (start_x == -1)
		return(1);
	char **mask = create_empty_map(height, width);
	if (!mask)
		return(1);
	flood_fill_masked(map->map, start_x, start_y, width, height, mask);
	map->map = build_filtered_map(map->map, mask, height, width);
	for (int i = 0; i < height; i++)
		free(mask[i]);
	free(mask);
	return(0);
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
	check_map_flood(map);
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

