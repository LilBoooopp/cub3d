/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbopp <cbopp@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 18:27:36 by cbopp             #+#    #+#             */
/*   Updated: 2025/06/19 16:45:36 by cbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_anim(t_cub *c)
{
	int	i;

	mlx_destroy_image(c->mlx, c->hud.anim_idle.img);
	i = 0;
	while (i < 4)
		mlx_destroy_image(c->mlx, c->hud.anim_shoot[i++].img);
	i = 0;
	while (i < 9)
		mlx_destroy_image(c->mlx, c->hud.anim_reload[i++].img);
	free(c->hud.anim_reload);
	free(c->hud.anim_shoot);
}

static void	destroy_textures(t_cub *c)
{
	mlx_destroy_image(c->mlx, c->north.img);
	mlx_destroy_image(c->mlx, c->east.img);
	mlx_destroy_image(c->mlx, c->south.img);
	mlx_destroy_image(c->mlx, c->west.img);
	free(c->tex.we);
	free(c->tex.n);
	free(c->tex.s);
	free(c->tex.ea);
	free_anim(c);
}

int	close_window(t_cub *cub)
{
	int	y;

	destroy_textures(cub);
	ft_free_chartable(cub->map->map);
	y = -1;
	while (++y < cub->map->sizey)
		free(cub->map->explored[y]);
	free(cub->map->explored);
	free(cub->map);
	mlx_destroy_window(cub->mlx, cub->mlx_win);
	mlx_destroy_display(cub->mlx);
	free(cub->mlx);
	exit(0);
}
