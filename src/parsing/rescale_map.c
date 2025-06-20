/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rescale_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbuet <pbuet@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 17:14:20 by pbuet             #+#    #+#             */
/*   Updated: 2025/06/20 14:17:27 by pbuet            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"parsing.h"

int	is_adjacent_to_non_wall(char **map, int y, int x, t_map strmap)
{
	const char		*non_walls;
	t_directions	dir;
	int				i;

	if (create_directions(&dir))
		return (2);
	non_walls = "0NSEW";
	i = 0;
	while (i < 8)
	{
		if (y + dir.dy[i] >= 0 && y + dir.dy[i] < strmap.sizey
			&& x + dir.dx[i] >= 0 && x + dir.dx[i] < strmap.sizex)
		{
			if (ft_strchr(non_walls, map[y + dir.dy[i]][x + dir.dx[i]]))
			{
				free(dir.dx);
				free(dir.dy);
				return (1);
			}
		}
		i ++;
	}
	free(dir.dx);
	free(dir.dy);
	return (0);
}

void	cleaning_walls(t_map strmap, char **cropped
						, int new_height, int new_width)
{
	int		x;
	int		y;

	y = -1;
	while (++y < new_height)
	{
		x = -1;
		while (++x < new_width)
		{
			if (strmap.map[strmap.tmp_y + y][strmap.tmp_x + x] == '1')
			{
				if (!is_adjacent_to_non_wall
					(strmap.map, strmap.tmp_y + y, strmap.tmp_x + x, strmap))
					strmap.map[strmap.tmp_y + y][strmap.tmp_x + x] = ' ';
			}
			cropped[y][x] = strmap.map[strmap.tmp_y + y][strmap.tmp_x + x];
		}
	}
}

char	**croccroc(t_map map, int new_height, int new_width)
{
	char	**cropped;
	int		y;
	int		x;

	y = 0;
	cropped = malloc(sizeof(char *) * (new_height + 1));
	while (y < new_height)
	{
		x = -1;
		cropped[y] = malloc(new_width + 1);
		while (++x < new_width)
			cropped[y][x] = map.map[map.tmp_y + y][map.tmp_x + x];
		cropped[y][new_width] = '\0';
		y ++;
	}
	cropped[new_height] = NULL;
	return (cropped);
}

void	find_map_bound(t_map *strmap, int *max_x, int *max_y)
{
	int	x;
	int	y;

	y = -1;
	strmap->tmp_x = strmap->sizex;
	strmap->tmp_y = strmap->sizey;
	while (++y < strmap->sizey)
	{
		x = -1;
		while (++x < strmap->sizex)
		{
			if (strmap->map[y][x] != '1' && strmap->map[y][x] != ' ')
			{
				if (x < strmap->tmp_x)
					strmap->tmp_x = x;
				if (x > *max_x)
					*max_x = x;
				if (y < strmap->tmp_y)
					strmap->tmp_y = y;
				if (y > *max_y)
					*max_y = y;
			}
		}
	}
}

char	**rescale(t_map *strmap)
{
	int		max_x;
	int		max_y;
	int		new_height;
	int		new_width;
	char	**cropped;

	max_x = 0;
	max_y = 0;
	find_map_bound(strmap, &max_x, &max_y);
	if (strmap->tmp_x > 0)
		strmap->tmp_x--;
	if (strmap->tmp_y > 0)
		strmap->tmp_y--;
	if (max_x < strmap->sizex - 1)
		max_x++;
	if (max_y < strmap->sizey - 1)
		max_y++;
	new_width = max_x - strmap->tmp_x + 1;
	new_height = max_y - strmap->tmp_y + 1;
	cropped = croccroc(*strmap, new_height, new_width);
	cleaning_walls(*strmap, cropped, new_height, new_width);
	strmap->sizex = new_width;
	strmap->sizey = new_height;
	ft_free_chartable(strmap->map);
	return (cropped);
}
