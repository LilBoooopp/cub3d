/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbopp <cbopp@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 21:09:15 by cbopp             #+#    #+#             */
/*   Updated: 2025/06/18 23:17:31 by cbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	*build_cols(t_map *m)
{
	int	*cols;
	int	i;

	cols = malloc(sizeof(int) * (m->sizex + 1));
	if (!cols)
		return (NULL);
	i = 0;
	while (i <= m->sizex)
	{
		cols[i] = (int)(i * m->t_size.x + 0.5);
		i++;
	}
	return (cols);
}

int	*build_rows(t_map *m)
{
	int	*rows;
	int	i;

	rows = malloc(sizeof(int) * (m->sizey + 1));
	if (!rows)
		return (NULL);
	i = 0;
	while (i <= m->sizey)
	{
		rows[i] = (int)(i * m->t_size.y + 0.5);
		i++;
	}
	return (rows);
}

void	draw_cells(t_map *m, t_img *map, int *cols, int *rows)
{
	t_vec2i	idx;
	int		col;
	t_vec2i	delta;
	int		w;

	idx.y = -1;
	while (++idx.y < m->sizey)
	{
		idx.x = -1;
		while (++idx.x < m->sizex)
		{
			if (m->map[idx.y][idx.x] == '1')
				col = MAP_WALL;
			else if (m->map[idx.y][idx.x] == '0')
				col = MAP_EMPTY;
			else
				continue ;
			delta.x = cols[idx.x];
			delta.y = rows[idx.y];
			w = cols[idx.x + 1] - delta.x;
			draw_rect(map, set_vec2((double)delta.x, (double)delta.y), set_vec2(
					(double)w, (double)(rows[idx.y + 1] - delta.y)), col);
		}
	}
}
