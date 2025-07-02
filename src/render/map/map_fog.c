/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_fog.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbopp <cbopp@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 23:35:53 by cbopp             #+#    #+#             */
/*   Updated: 2025/07/02 16:58:23 by cbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	is_within_fov(t_vec2 dir, t_vec2 pl_dir)
{
	double	len;
	double	dot;

	len = sqrt(dir.x * dir.x + dir.y * dir.y);
	if (len == 0)
		return (true);
	dot = (dir.x * pl_dir.x + dir.y * pl_dir.y) / len;
	return (dot >= 0.86);
}

bool	is_tile_visible(t_map *m, t_vec2 pl_pos, t_vec2i tile, t_vec2 pl_dir)
{
	t_vec2	pos;
	t_vec2	dir;
	int		steps;
	int		i;

	dir.x = tile.x + 0.5 - pl_pos.x;
	dir.y = tile.y + 0.5 - pl_pos.y;
	if (!is_within_fov(dir, pl_dir))
		return (false);
	steps = sqrt(dir.x * dir.x + dir.y * dir.y) * 10;
	dir.x /= steps;
	dir.y /= steps;
	pos = pl_pos;
	i = 0;
	while (i++ < steps)
	{
		if ((int)pos.x == tile.x && (int)pos.y == tile.y)
			return (true);
		if (m->map[(int)pos.y][(int)pos.x] == '1'
			|| m->map[(int)pos.y][(int)pos.x] == 'P')
			return ((int)pos.x == tile.x && (int)pos.y == tile.y);
		pos.x += dir.x;
		pos.y += dir.y;
	}
	return (true);
}

void	reveal_surr(t_map *map, t_vec2 pos, int radius)
{
	int	x;
	int	y;
	int	i;
	int	j;

	y = (int)pos.y;
	x = (int)pos.x;
	i = -radius;
	while (i <= radius)
	{
		j = -radius;
		while (j <= radius)
		{
			if (y + i >= 0 && y + i < map->sizey
				&& x + j >= 0 && x + j < map->sizex)
				map->explored[y + i][x + j] = true;
			j++;
		}
		i++;
	}
}
