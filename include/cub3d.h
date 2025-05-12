/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbopp <cbopp@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 14:47:37 by cbopp             #+#    #+#             */
/*   Updated: 2025/05/10 12:58:09 by cbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <../mlx_linux/mlx.h>
# include <stdio.h>
# include <math.h>
# include <stdlib.h>

typedef enum e_direction
{
	N,
	E,
	S,
	W
};

typedef struct s_cub
{
	void	*mlx;
	void	*mlx_win;
}	t_cub;

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_length;
	int		endian;
}	t_data;

// init
int		init(t_cub *cub);

// mlx
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);


#endif