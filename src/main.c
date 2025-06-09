/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbuet <pbuet@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 16:55:19 by cbopp             #+#    #+#             */
/*   Updated: 2025/06/09 17:09:10 by pbuet            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int ac, char **av)
{
	t_cub	cub;

	if (ac != 2)
		return(1);
	ft_bzero(&cub, sizeof(cub));
	if (init(&cub, av))
		return (1);
	mlx_hook(cub.mlx_win, 2, 1l << 0, handle_input, &cub);
	mlx_hook(cub.mlx_win, 3, 1L << 1, handle_keyrelease, &cub);
	mlx_hook(cub.mlx_win, 17, 0, close_window, &cub);
	mlx_loop_hook(cub.mlx, update, &cub);
	mlx_loop(cub.mlx);
	close_window(&cub);
	return (0);
}
