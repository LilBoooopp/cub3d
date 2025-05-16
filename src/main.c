/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbopp <cbopp@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 16:55:19 by cbopp             #+#    #+#             */
/*   Updated: 2025/05/16 15:43:44 by cbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	main(void)
{
	t_cub	cub;

	init(&cub);
	mlx_hook(cub.mlx_win, 2, 1l << 0, handle_input, &cub);
	mlx_hook(cub.mlx_win, 3, 1L << 1, handle_keyrelease, &cub);
	mlx_hook(cub.mlx_win, 17, 0, close_window, &cub);
	mlx_loop_hook(cub.mlx, render, &cub);
	mlx_loop(cub.mlx);
	return (0);
}
