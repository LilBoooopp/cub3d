/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbopp <cbopp@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 14:47:37 by cbopp             #+#    #+#             */
/*   Updated: 2025/05/12 16:52:41 by cbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <../mlx_linux/mlx.h>
# include <stdio.h>
# include <math.h>
# include <stdlib.h>
# include "../libft/libft.h"

typedef enum e_direction
{
	N,
	E,
	S,
	W
}	t_direction;

typedef struct s_vec2
{
	float	x;
	float	y;
}	t_vec2;

typedef struct s_vec3
{
	float	x;
	float	y;
	float	z;
}	t_vec3;

typedef struct s_vec4
{
	int	r;
	int	g;
	int	b;
	int	a;
}	t_vec4;

typedef struct s_player
{
	t_vec2	pos;
	float	facing;
	int		fov;
}	t_player;

typedef struct s_map
{
	int	sizex;
	int	sizey;
	int	**map;
}	t_map;

typedef struct s_cub
{
	void		*mlx;
	void		*mlx_win;
	t_player	player;
	t_map		*map;
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