/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_fog.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbopp <cbopp@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 23:35:53 by cbopp             #+#    #+#             */
/*   Updated: 2025/06/18 23:38:28 by cbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
