/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gen_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbuet <pbuet@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 11:04:25 by plbuet            #+#    #+#             */
/*   Updated: 2025/06/26 15:50:08 by pbuet            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"bsp.h"

char	**create_empty_map(int height, int width)
{
	char	**map;
	int		y;

	y = 0;
	map = malloc(sizeof(char *) * (height + 1));
	if (!map)
		return (NULL);
	while (y < height)
	{
		map[y] = malloc(width + 1);
		if (!map[y])
			return (NULL);
		ft_memset(map[y], '1', width);
		map[y][width] = '\0';
		y ++;
	}
	map[height] = NULL;
	return (map);
}

void	draw_line(	int x1, int y1, int x2, int y2, char **map)
{
	int x;
	int y;

	x = fmin(x1, x2);
	while (x <= fmax(x1, x2))
	{
		map[y1][x] = '0';
		x ++;
	}
	y = fmin(y1, y2);
	while (y <= fmax(y1, y2))
	{
		map[y][x2] = '0';
		y ++;
	}
}
void	midle_square(t_bsp *node, char **map)
{
	int x1;
	int y1;
	int x2;
	int y2;

	x1 = node->left->rmidle_x;
	y1 = node->left->rmidle_y;
	x2 = node->right->rmidle_x;
	y2 = node->right->rmidle_y;
	node->rmidle_x = x1;
	node->rmidle_y = y1;
	draw_line(x1, y1, x2, y2, map);
}
void	find_line_map(t_bsp *node, char **map)
{
	if (!node)
		return;
	if (!node->left && !node->right && node->room)
	{
		node->rmidle_x = node->room->x + node->room->width  / 2;
		node->rmidle_y = node->room->y + node->room->height / 2;
		return;
	}
	find_line_map(node->left, map);
	find_line_map(node->right, map);
	midle_square(node, map);
}

void	map_draw_rooms(t_bsp *node, char **map)
{
	int	x;
	int	y;

	y = 1;
	if (!node)
		return;
	if (!node->left && !node->right && node->room)
	{
		while (y < node->room->height - 1)
		{
			x = 1;
			while (x < node->room->width - 1)
			{
				map[node->room->y + y][node->room->x + x] = '0';
				x ++;
			}
			y ++;
		}
	}
	else
	{
		map_draw_rooms(node->left, map);
		map_draw_rooms(node->right, map);
	}
}
