/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbopp <cbopp@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 14:47:37 by cbopp             #+#    #+#             */
/*   Updated: 2025/05/12 23:35:29 by cbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../mlx_linux/mlx.h"
# include <stdio.h>
# include <math.h>
# include <stdlib.h>
# include "../libft/libft.h"

# define WIN_WIDTH 1280
# define WIN_HEIGHT 1080

# define MOVE_SPEED 5.0
# define ROT_SPEED 0.05

typedef enum e_key
{
	key_W = 119,
	key_A = 97,
	key_S = 115,
	key_D = 100,
	key_LEFT = 65361,
	key_RIGHT = 65363,
	key_ESC = 65307
}	t_key;

typedef struct s_vec2
{
	double	x;
	double	y;
}	t_vec2;

typedef struct s_vec3
{
	double	x;
	double	y;
	double	z;
}	t_vec3;

typedef struct s_vec4
{
	int	r;
	int	g;
	int	b;
	int	a;
}	t_vec4;

/**
 * @brief player struct
 * @param pos Player position vector.
 * @param dir Player direct vector.
 * @param plane Player camera vector.
 */
typedef struct s_player
{
	t_vec2	pos;
	t_vec2	dir;
	t_vec2	plane;
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

typedef struct s_img
{
	void	*img;
	t_vec2	size;
	char	*addr;
	int		bpp;
	int		len;
	int		end;
}	t_img;

// init
int		init(t_cub *cub);

// utils
t_vec2	set_vec2(double x, double y);
t_vec3	set_vec3(double x, double y, double z);
t_vec4	set_vec4(int r, int g, int b, int a);
int		is_in_bounds(t_img *img, t_vec2 point);
t_vec2	get_center(t_img *img);

int		handle_input(int keycode, t_cub *cub);
int		close_window(t_cub *cub);

// render
int		render(t_cub *cub);

// player
void	move_forward(t_player *p);
void	move_backward(t_player *p);
void	move_right(t_player *p);
void	move_left(t_player *p);
void	rotate(t_player *p, double angle);

// mlx
int		get_pixel(t_img *img, t_vec2 pos);
void	mlx_set_img(t_img *img, int color);
void	my_mlx_pixel_put(t_img *data, int x, int y, int color);
void	draw_pixels(t_img *img, t_vec2 pos, t_vec2 size, int color);

// draw
void	draw_line(t_img *img, t_vec2 start, t_vec2 end, int color);
void	draw_rotated_image(t_img *target, t_img *source, t_vec2 pos,
	double angle);

#endif