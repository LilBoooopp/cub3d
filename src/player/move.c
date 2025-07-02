/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbopp <cbopp@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 19:41:35 by cbopp             #+#    #+#             */
/*   Updated: 2025/07/02 16:53:11 by cbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_forward(t_player *p, t_map *m, double spd)
{
	t_vec2	n;

	n.x = p->pos.x + p->dir.x * spd;
	n.y = p->pos.y + p->dir.y * spd;
	if (m->map[(int)p->pos.y][(int)n.x] == '0'
		|| m->map[(int)p->pos.y][(int)n.x] == 'O')
		p->pos.x = n.x / TILE_SIZE;
	if (m->map[(int)n.y][(int)p->pos.x] == '0'
		|| m->map[(int)n.y][(int)p->pos.x] == 'O')
		p->pos.y = n.y / TILE_SIZE;
}

void	move_backward(t_player *p, t_map *m, double spd)
{
	t_vec2	n;

	n.x = p->pos.x - p->dir.x * spd;
	n.y = p->pos.y - p->dir.y * spd;
	if (m->map[(int)p->pos.y][(int)n.x] == '0'
		|| m->map[(int)p->pos.y][(int)n.x] == 'O')
		p->pos.x = n.x / TILE_SIZE;
	if (m->map[(int)n.y][(int)p->pos.x] == '0'
		|| m->map[(int)n.y][(int)p->pos.x] == 'O')
		p->pos.y = n.y / TILE_SIZE;
}

void	move_right(t_player *p, t_map *m, double spd)
{
	t_vec2	n;

	n.x = p->pos.x - p->dir.y * spd;
	n.y = p->pos.y + p->dir.x * spd;
	if (m->map[(int)p->pos.y][(int)n.x] == '0'
		|| m->map[(int)p->pos.y][(int)n.x] == 'O')
		p->pos.x = n.x / TILE_SIZE;
	if (m->map[(int)n.y][(int)p->pos.x] == '0'
		|| m->map[(int)n.y][(int)p->pos.x] == 'O')
		p->pos.y = n.y / TILE_SIZE;
}

void	move_left(t_player *p, t_map *m, double spd)
{
	t_vec2	n;

	n.x = p->pos.x + p->dir.y * spd;
	n.y = p->pos.y - p->dir.x * spd;
	if (m->map[(int)p->pos.y][(int)n.x] == '0'
		|| m->map[(int)p->pos.y][(int)n.x] == 'O')
		p->pos.x = n.x / TILE_SIZE;
	if (m->map[(int)n.y][(int)p->pos.x] == '0'
		|| m->map[(int)n.y][(int)p->pos.x] == 'O')
		p->pos.y = n.y / TILE_SIZE;
}

void	rotate(t_player *p, double angle)
{
	double	old_dir;
	double	old_plane;
	double	c;
	double	s;

	c = cos(angle);
	s = sin(angle);
	old_dir = p->dir.x;
	old_plane = p->plane.x;
	p->dir.x = p->dir.x * c - p->dir.y * s;
	p->dir.y = old_dir * s + p->dir.y * c;
	p->plane.x = p->plane.x * c - p->plane.y * s;
	p->plane.y = old_plane * s + p->plane.y * c;
}
