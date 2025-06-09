/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbuet <pbuet@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 18:27:36 by cbopp             #+#    #+#             */
/*   Updated: 2025/06/09 16:28:20 by pbuet            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	destroy_textures(t_cub *c)
{
	mlx_destroy_image(c->mlx, c->north.img);
	mlx_destroy_image(c->mlx, c->east.img);
	mlx_destroy_image(c->mlx, c->south.img);
	mlx_destroy_image(c->mlx, c->west.img);
}

int	close_window(t_cub *cub)
{
	free(cub->tex.we);
	free(cub->tex.n);
	free(cub->tex.s);
	free(cub->tex.ea);
	destroy_textures(cub);
	ft_free_chartable(cub->map->map);
	mlx_destroy_window(cub->mlx, cub->mlx_win);
	mlx_destroy_display(cub->mlx);
	exit(0);
}
