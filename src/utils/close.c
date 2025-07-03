/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbopp <cbopp@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 18:27:36 by cbopp             #+#    #+#             */
/*   Updated: 2025/07/03 12:25:09 by cbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	destroy_textures(t_cub *c)
{
	if (c->north.img != NULL)
		mlx_destroy_image(c->mlx, c->north.img);
	if (c->east.img != NULL)
		mlx_destroy_image(c->mlx, c->east.img);
	if (c->south.img != NULL)
		mlx_destroy_image(c->mlx, c->south.img);
	if (c->west.img != NULL)
		mlx_destroy_image(c->mlx, c->west.img);
	if (c->doors.img != NULL)
		mlx_destroy_image(c->mlx, c->doors.img);
	free(c->tex.we);
	free(c->tex.n);
	free(c->tex.s);
	free(c->tex.ea);
	free(c->tex.door);
	free(c->tex.f);
	free(c->tex.c);
}

void	free_xpm(t_cub *c, int error)
{
	if (error == 1)
	{
		free(c->hud.anim_shoot);
		free(c->hud.anim_reload);
		error_msg("Failed to load an animation xpm file");
	}
	destroy_textures(c);
	free_map(c);
	mlx_destroy_display(c->mlx);
	free(c->mlx);
	if (error != 1)
		error_msg("Failed to load an xpm file");
	exit(1);
}

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

int	close_window(t_cub *cub)
{
	destroy_textures(cub);
	if (IS_HUD)
		free_anim(cub);
	free_map(cub);
	mlx_destroy_window(cub->mlx, cub->mlx_win);
	mlx_destroy_display(cub->mlx);
	free(cub->mlx);
	exit(0);
}
