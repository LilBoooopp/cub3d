/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbopp <cbopp@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 21:15:56 by cbopp             #+#    #+#             */
/*   Updated: 2025/05/17 21:19:23 by cbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	put(t_cub *c, int y, char *s, int sel)
{
	int	col;

	if (sel)
		col = 0xFFFF00;
	else
		col = 0xFFFFFF;
	mlx_string_put(c->mlx, c->mlx_win, 40, y, col, s);
}

void	draw_menu(t_cub *c)
{
	mlx_clear_window(c->mlx, c->mlx_win);
	put(c, 100, "CUB3D", 0);
	put(c, 100, "PLAY", c->menu_sel == 0);
	put(c, 230, "TOGGLE DEBUG", c->menu_sel == 1);
	put(c, 260, "QUIT", c->menu_sel == 2);
}
