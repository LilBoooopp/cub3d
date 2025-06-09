/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbopp <cbopp@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 18:27:36 by cbopp             #+#    #+#             */
/*   Updated: 2025/06/09 19:46:53 by cbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
}

int	close_window(t_cub *cub)
{

	destroy_textures(cub);
	ft_free_chartable(cub->map->map);
	free(cub->map);
	mlx_destroy_window(cub->mlx, cub->mlx_win);
	mlx_destroy_display(cub->mlx);
	free(cub->mlx);
	exit(0);
}
