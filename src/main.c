/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbopp <cbopp@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 16:55:19 by cbopp             #+#    #+#             */
/*   Updated: 2025/08/20 17:13:49 by cbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int ac, char **av)
{
	t_cub	cub;

	if (ac != 2)
	{
		errno = EINVAL;
		error_msg("Only 1 arguement is permitted");
		return (1);
	}
	ft_bzero(&cub, sizeof(cub));
	if (init(&cub, av))
		return (1);
	// mlx_mouse_hide(cub.mlx, cub.mlx_win);
	center_mouse(&cub);
	mlx_hook(cub.mlx_win, 2, 1l << 0, handle_input, &cub);
	mlx_hook(cub.mlx_win, 3, 1L << 1, handle_keyrelease, &cub);
	mlx_hook(cub.mlx_win, 4, 1L << 2, mouse_press_handler, &cub);
	mlx_hook(cub.mlx_win, 6, 1L << 6, mouse_move, &cub);
	mlx_hook(cub.mlx_win, 17, 0, close_window, &cub);
	mlx_loop_hook(cub.mlx, update, &cub);
	mlx_loop(cub.mlx);
	close_window(&cub);
	return (0);
}
