/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbopp <cbopp@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 21:15:56 by cbopp             #+#    #+#             */
/*   Updated: 2025/06/18 23:34:10 by cbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	handle_menu(int key, t_cub *c)
{
	if (c->state == STATE_MENU)
	{
		if (key == KEY_UP && c->menu_sel > 0)
			c->menu_sel--;
		else if (key == KEY_DOWN && c->menu_sel < 2)
			c->menu_sel++;
		else if (key == KEY_ENTER)
		{
			if (c->menu_sel == 0)
				c->state = STATE_PLAY;
			else if (c->menu_sel == 1)
				c->debug ^= 1;
			else if (c->menu_sel == 2)
				close_window(c);
		}
		return (0);
	}
	return (0);
}

static void	put(t_cub *c, int y, char *s, int sel)
{
	int	col;

	if (sel)
		col = 0xFFFF00;
	else
		col = 0xFFFFFF;
	mlx_string_put(c->mlx, c->mlx_win, 600, y, col, s);
}

void	draw_menu(t_cub *c)
{
	mlx_clear_window(c->mlx, c->mlx_win);
	put(c, 100, "CUB3D", 0);
	put(c, 200, "PLAY", c->menu_sel == 0);
	put(c, 230, "TOGGLE DEBUG", c->menu_sel == 1);
	put(c, 260, "QUIT", c->menu_sel == 2);
}
