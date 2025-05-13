/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbopp <cbopp@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 14:47:37 by cbopp             #+#    #+#             */
/*   Updated: 2025/05/13 18:30:24 by cbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# if defined(__APPLE__)
#	include "../mlx_mac/mlx.h"
# else
#	include "../mlx_linux/mlx.h"
# endif

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

typedef struct s_vec2i
{
	int	x;
	int	y;
}	t_vec2i;

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

typedef struct s_raycast
{
	double	cam_x;
	t_vec2	ray_dir;
	t_vec2i	map;
	t_vec2	side_dist;
	t_vec2	delta_dist;
	t_vec2i	step;
	int		hit;
	int		side;
	double	perp_dist;
	int		line_h;
	int		draw_start;
	int		draw_end;
	int		color;
}	t_raycast;

typedef struct s_img
{
	void	*img;
	t_vec2	size;
	char	*addr;
	int		bpp;
	int		len;
	int		end;
}	t_img;

/* === AUTO GENERATED PROTOTYPES START === */
/* init */
int	init(t_cub *cub);
void	init_player(t_player *player);

/* mlx */
int	get_pixel(t_img *img, t_vec2 pos);
t_img	make_image(t_cub *cub, t_vec2 size, int color);
t_vec2	get_rotated_position(t_vec2 center, t_vec2 local, double angle);
t_vec2	rotate_point(t_vec2 rel, double angle);
void	draw_line(t_img *img, t_vec2 start, t_vec2 end, int color);
void	draw_pixels(t_img *img, t_vec2 pos, t_vec2 size, int color);
void	draw_rotated_image(t_img *t, t_img *s, t_vec2 pos, double ang);
void	drawtoimg(t_img *src, t_img *dst, t_vec2 pos);
void	mlx_set_img(t_img *img, unsigned int color);
void	my_mlx_pixel_put(t_img *data, int x, int y, int color);

/* player */
void	move_backward(t_player *p);
void	move_forward(t_player *p);
void	move_left(t_player *p);
void	move_right(t_player *p);
void	rotate(t_player *p, double angle);

/* render */
int	render(t_cub *cub);
t_vec2i	set_raydir(t_raycast ray);
void	cast_rays(t_cub *cub);
void	draw_dir(t_player *p, t_vec2 map_pos, t_img *map);
void	draw_player(t_cub *cub, t_player *player, t_img *img, t_img *map);
void	render_map(t_cub *cub, t_img *img, t_player *player);
void	setSideDist(t_raycast *ray, t_player player);

/* utils */
int	close_window(t_cub *cub);
int	handle_input(int keycode, t_cub *cub);
int	is_in_bounds(t_img *img, t_vec2 point);
t_vec2	fix_pos(t_img *src, t_img *dst, t_vec2 pos);
t_vec2	get_center(t_img *img);
t_vec2	set_vec2(double x, double y);
t_vec2	vec2_add(t_vec2 vec1, t_vec2 vec2);
t_vec2	vec2_div(t_vec2 vec1, t_vec2 vec2);
t_vec2	vec2_mult(t_vec2 vec1, t_vec2 vec2);
t_vec2	vec2_sub(t_vec2 vec1, t_vec2 vec2);
t_vec2i	vecdtoi(t_vec2 vec2);
t_vec3	set_vec3(double x, double y, double z);
t_vec4	set_vec4(int r, int g, int b, int a);

/* === AUTO GENERATED PROTOTYPES END   === */

#endif
