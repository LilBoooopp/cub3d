/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbuet <pbuet@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 16:55:19 by cbopp             #+#    #+#             */
/*   Updated: 2025/05/27 16:07:10 by pbuet            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// int	main(int ac, char **av)
// {
// 	t_cub	cub;

// 	if (ac != 2)
// 		return(1);
// 	if (init(&cub, av))
// 		return (1);
// 	mlx_hook(cub.mlx_win, 2, 1l << 0, handle_input, &cub);
// 	mlx_hook(cub.mlx_win, 3, 1L << 1, handle_keyrelease, &cub);
// 	mlx_hook(cub.mlx_win, 17, 0, close_window, &cub);
// 	mlx_loop_hook(cub.mlx, update, &cub);
// 	mlx_loop(cub.mlx);
// 	return (0);
// }


int	main(void)
{
	void	*mlx;
	void	*win;
	void	*img;
	int		img_w;
	int		img_h;
	int		win_w = 800;
	int		win_h = 600;
	int		x, y;

	mlx = mlx_init();
	win = mlx_new_window(mlx, win_w, win_h, "Motif XPM");

	// Charge le motif
	img = mlx_xpm_file_to_image(mlx, "pattern.xpm", &img_w, &img_h);
	if (!img)
		return (1);

	// Répète l'image sur toute la fenêtre
	y = 0;
	while (y < win_h)
	{
		x = 0;
		while (x < win_w)
		{
			mlx_put_image_to_window(mlx, win, img, x, y);
			x += img_w;
		}
		y += img_h;
	}

	mlx_loop(mlx);
	return (0);
}
