/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbopp <cbopp@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 14:47:37 by cbopp             #+#    #+#             */
/*   Updated: 2025/05/19 18:40:42 by cbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# if defined(__APPLE__)
#  include "../mlx_mac/mlx.h"
#  define key_A		0x00
#  define key_B		0x0B
#  define key_C		0x08
#  define key_D		0x02
#  define key_E		0x0E
#  define key_F		0x03
#  define key_G		0x05
#  define key_H		0x04
#  define key_I		0x22
#  define key_J		0x26
#  define key_K		0x28
#  define key_L		0x25
#  define key_M		0x2E
#  define key_N		0x2D
#  define key_O		0x1F
#  define key_P		0x23
#  define key_Q		0x0C
#  define key_R		0x0F
#  define key_S		0x01
#  define key_T		0x11
#  define key_U		0x20
#  define key_V		0x09
#  define key_W		0x0D
#  define key_X		0x07
#  define key_Y		0x10
#  define key_Z		0x06
#  define key_LEFT	0x7B
#  define key_RIGHT	0x7C
#  define key_ESC	0x35
# else
#  include "../mlx_linux/mlx.h"
#  define key_A		'a'
#  define key_B		'b'
#  define key_C		'c'
#  define key_D		'd'
#  define key_E		'e'
#  define key_F		'f'
#  define key_G		'g'
#  define key_H		'h'
#  define key_I		'i'
#  define key_J		'j'
#  define key_K		'k'
#  define key_L		'l'
#  define key_M		'm'
#  define key_N		'n'
#  define key_O		'o'
#  define key_P		'p'
#  define key_Q		'q'
#  define key_R		'r'
#  define key_S		's'
#  define key_T		't'
#  define key_U		'u'
#  define key_V		'v'
#  define key_W		'w'
#  define key_X		'x'
#  define key_Y		'y'
#  define key_Z		'z'
#  define key_LEFT	65361
#  define key_RIGHT	65363
#  define key_ESC 	65307
# endif

# include <stdio.h>
#include <fcntl.h>
# include <math.h>
# include <stdlib.h>
# include <ctype.h>
# include <stdbool.h>
# include <time.h>
# include "../libft/libft.h"
# include <sys/time.h>

# define WIN_WIDTH 1280
# define WIN_HEIGHT 1080

# define MOVE_SPEED 3.0
# define ROT_SPEED 2.0
# define TILE_SIZE 1

extern const char	*g_digit[10];

typedef enum e_state
{
	STATE_MENU,
	STATE_PLAY
}	t_state;

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
	int		sizex;
	int		sizey;
	char	**map;
	char	orientation;
	int		player_x;
	int		player_y;
}	t_map;

typedef struct s_texture
{
	char	*n;
	char	*s;
	char	*we;
	char	*ea;
	char	f[7];
	char	c[7];
	int		full;
}	t_texture;

typedef struct s_cub
{
	void		*mlx;
	void		*mlx_win;
	t_player	player;
	t_map		*map;
	t_texture	texture;
	int			debug;
	bool		keys[70000];
	double		frame_time;
	double		last_frame_time;
	double		delta;
	int			fps;
	t_state		state;
	int			menu_sel;
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
double	gettime(void);
t_map	*ini_map(t_cub *cub, char **v);
int		init(t_cub *cub, char ** v);
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
void	move_backward(t_player *p, t_map *m, double spd);
void	move_forward(t_player *p, t_map *m, double spd);
void	move_left(t_player *p, t_map *m, double spd);
void	move_right(t_player *p, t_map *m, double spd);
void	rotate(t_player *p, double angle);

/* render */
int	render(t_cub *cub);
int	update(t_cub *cub);
t_vec2i	set_raydir(t_raycast *ray);
void	cast_rays(t_cub *cub, t_img *img);
void	change_debug(t_cub *cub);
void	draw_big_fps(t_cub *cub);
void	draw_debug(t_cub *cub);
void	draw_digit(t_cub *c, char d, int ox, int oy, int s);
void	draw_dir(t_player *p, t_vec2 map_pos, t_img *map);
void	draw_player(t_cub *cub, t_player *player, t_img *map);
void	draw_px(t_cub *c, int x, int y);
void	init_ray(t_cub *cub, t_raycast *ray, int x);
void	render_map(t_cub *cub, t_img *img, t_player *player);
void	set_side_dist(t_raycast *ray, t_player player);

/* utils */
int	close_window(t_cub *cub);
int	handle_input(int keycode, t_cub *cub);
int	handle_keyrelease(int kc, t_cub *cub);
int	is_in_bounds(t_img *img, t_vec2 point);
t_vec2	fix_pos(t_cub *cub, t_img *dst, t_vec2 pos);
t_vec2	get_center(t_img *img);
t_vec2	set_vec2(double x, double y);
t_vec2	vec2_add(t_vec2 vec1, t_vec2 vec2);
t_vec2	vec2_div(t_vec2 vec1, t_vec2 vec2);
t_vec2	vec2_mult(t_vec2 vec1, t_vec2 vec2);
t_vec2	vec2_sub(t_vec2 vec1, t_vec2 vec2);
t_vec2i	vecdtoi(t_vec2 vec2);
t_vec3	set_vec3(double x, double y, double z);
t_vec4	set_vec4(int r, int g, int b, int a);
void	smooth_input(t_cub *cub);

/* === AUTO GENERATED PROTOTYPES END   === */

#endif
