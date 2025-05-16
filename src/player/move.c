/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbopp <cbopp@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 19:41:35 by cbopp             #+#    #+#             */
/*   Updated: 2025/05/16 16:14:08 by cbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_forward(t_player *p, t_map *m)
{
	t_vec2	n;

	n.x = p->pos.x + p->dir.x * MOVE_SPEED;
	n.y = p->pos.y + p->dir.y * MOVE_SPEED;
	if (m->map[(int)p->pos.y][(int)n.x] == '0')
		p->pos.x = n.x;
	if (m->map[(int)n.y][(int)p->pos.x] == '0')
		p->pos.y = n.y;
}

void	move_backward(t_player *p, t_map *m)
{
	t_vec2	n;

	n.x = p->pos.x - p->dir.x * MOVE_SPEED;
	n.y = p->pos.y - p->dir.y * MOVE_SPEED;
	if (m->map[(int)p->pos.y][(int)n.x] == '0')
		p->pos.x = n.x;
	if (m->map[(int)n.y][(int)p->pos.x] == '0')
		p->pos.y = n.y;
}

void	move_right(t_player *p, t_map *m)
{
	t_vec2	n;

	n.x = p->pos.x - p->dir.y * MOVE_SPEED;
	n.y = p->pos.y + p->dir.x * MOVE_SPEED;
	if (m->map[(int)p->pos.y][(int)n.x] == '0')
		p->pos.x = n.x;
	if (m->map[(int)n.y][(int)p->pos.x] == '0')
		p->pos.y = n.y;
}

void	move_left(t_player *p, t_map *m)
{
	t_vec2	n;

	n.x = p->pos.x + p->dir.y * MOVE_SPEED;
	n.y = p->pos.y - p->dir.x * MOVE_SPEED;
	if (m->map[(int)p->pos.y][(int)n.x] == '0')
		p->pos.x = n.x;
	if (m->map[(int)n.y][(int)p->pos.x] == '0')
		p->pos.y = n.y;
}

void	rotate(t_player *p, double angle)
{
	double	old_dir;
	double	old_plane;

	old_dir = p->dir.x;
	old_plane = p->plane.x;
	p->dir.x = p->dir.x * cos(angle) - p->dir.y * sin(angle);
	p->dir.y = old_dir * sin(angle) + p->dir.y * cos(angle);
	p->plane.x = p->plane.x * cos(angle) - p->plane.y * sin(angle);
	p->plane.y = old_plane * sin(angle) + p->plane.y * cos(angle);
}
