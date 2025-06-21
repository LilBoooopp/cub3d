/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbuet <pbuet@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 20:11:33 by plbuet            #+#    #+#             */
/*   Updated: 2025/06/20 13:38:56 by pbuet            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"parsing.h"

int	flood_fill_masked(t_map map, int x, int y, char **mask)
{
	char	c;

	if (x < 0 || y < 0 || x == map.sizex || y == map.sizey)
		return (-1);
	c = map.map[y][x];
	if (c == ' ' || c == '\0')
		return (-1);
	if (c == '1' || mask[y][x] == 'x')
		return (0);
	mask[y][x] = 'x';
	if (flood_fill_masked(map, x + 1, y, mask) < 0)
		return (-1);
	if (flood_fill_masked(map, x - 1, y, mask) < 0)
		return (-1);
	if (flood_fill_masked(map, x, y + 1, mask) < 0)
		return (-1);
	if (flood_fill_masked(map, x, y - 1, mask) < 0)
		return (-1);
	return (0);
}

char	**build_filtered_map(char **original, char **mask
								, int width, int height)
{
	int		y;
	int		x;
	char	**filtered;

	y = 0;
	x = 0;
	filtered = malloc(sizeof(char *) * (height + 1));
	while (y < height)
	{
		filtered[y] = malloc(width + 1);
		x = 0;
		while (x < width)
		{
			if (mask[y][x] == 'x')
				filtered[y][x] = original[y][x];
			else
				filtered[y][x] = '1';
			x ++;
		}
		filtered[y][width] = '\0';
		y ++;
	}
	filtered[height] = NULL;
	ft_free_chartable(original);
	return (filtered);
}

int	check_map_flood(t_map *map, int max_width)
{
	char	**tmp;
	char	**mask;

	map->sizex = max_width;
	if (search_player(map, 0) < 0)
	{
		perror("Invalid map\n");
		return (1);
	}
	mask = create_empty_map(map->sizey, map->sizex);
	if (!mask)
		return (1);
	if (flood_fill_masked(*map, map->playerx, map->playery, mask) < 0)
	{
		ft_free_chartable(map->map);
		ft_free_chartable(mask);
		return (1);
	}
	tmp = build_filtered_map(map->map, mask, map->sizex, map->sizey);
	map->map = tmp;
	map->map = rescale(map);
	ft_free_chartable(mask);
	search_player(map, 0);
	return (0);
}

t_map	*tab_map(t_node *lst_map, int max_width)
{
	int		size;
	t_map	*map;

	size = ft_size(lst_map);
	map = malloc(sizeof(t_map));
	map->map = malloc(sizeof(char *) * (size + 1));
	if (!map->map || !map)
		return (NULL);
	map->sizey = size;
	node_map(map, max_width, lst_map, size);
	if (check_map_flood(map, max_width) == 1)
	{
		free(map);
		return (NULL);
	}
	return (map);
}

t_map	*read_map(int fd, char *line, int len, int max_width)
{
	t_node	*map_list;
	t_node	*new;
	t_node	*last;

	map_list = ft_new(line);
	free(line);
	last = map_list;
	line = get_next_line(fd);
	while (line)
	{
		len = ft_strlen(line);
		if (len > max_width)
			max_width = len;
		new = ft_new(line);
		if (!new)
			return (NULL);
		free(line);
		last->next = new;
		last = new;
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
	return (tab_map(map_list, max_width));
}
