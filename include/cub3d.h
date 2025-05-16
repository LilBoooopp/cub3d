/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plbuet <plbuet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 14:47:37 by cbopp             #+#    #+#             */
/*   Updated: 2025/05/16 15:44:08 by plbuet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <../mlx_linux/mlx.h>
# include <stdio.h>
# include <math.h>
# include <stdlib.h>
# include "../libft/libft.h"

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

typedef struct s_texture
{
	char	*n;
	char	*s;
	char	*we;
	char	*ea;
	char	f[7];
	char	c[7];
}	t_texture;

// mlx
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);


#endif