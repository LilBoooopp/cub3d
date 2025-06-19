/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbuet <pbuet@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 14:47:37 by cbopp             #+#    #+#             */
/*   Updated: 2025/06/19 18:27:53 by pbuet            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# if defined(__APPLE__)
#  include "../mlx_mac/mlx.h"
#  define KEY_A				0x00
#  define KEY_B				0x0B
#  define KEY_C				0x08
#  define KEY_D				0x02
#  define KEY_E				0x0E
#  define KEY_F				0x03
#  define KEY_G				0x05
#  define KEY_H				0x04
#  define KEY_I				0x22
#  define KEY_J				0x26
#  define KEY_K				0x28
#  define KEY_L				0x25
#  define KEY_M				0x2E
#  define KEY_N				0x2D
#  define KEY_O				0x1F
#  define KEY_P				0x23
#  define KEY_Q				0x0C
#  define KEY_R				0x0F
#  define KEY_S				0x01
#  define KEY_T				0x11
#  define KEY_U				0x20
#  define KEY_V				0x09
#  define KEY_W				0x0D
#  define KEY_X				0x07
#  define KEY_Y				0x10
#  define KEY_Z				0x06
#  define KEY_LEFT			0x7B
#  define KEY_RIGHT			0x7C
#  define KEY_UP			0x7A
#  define KEY_DOWN			0x7D
#  define KEY_ENTER			0x24
#  define KEY_ESC			0x35
#  define KEY_LCTRL			0x3B
#  define KEY_SPACE			0x31
#  define KEY_LEFT_CLICK	0x02
#  define KEY_RIGHT_CLICK	0x02
# else
#  include "../mlx_linux/mlx.h"
#  define KEY_A				'a'
#  define KEY_B				'b'
#  define KEY_C				'c'
#  define KEY_D				'd'
#  define KEY_E				'e'
#  define KEY_F				'f'
#  define KEY_G				'g'
#  define KEY_H				'h'
#  define KEY_I				'i'
#  define KEY_J				'j'
#  define KEY_K				'k'
#  define KEY_L				'l'
#  define KEY_M				'm'
#  define KEY_N				'n'
#  define KEY_O				'o'
#  define KEY_P				'p'
#  define KEY_Q				'q'
#  define KEY_R				'r'
#  define KEY_S				's'
#  define KEY_T				't'
#  define KEY_U				'u'
#  define KEY_V				'v'
#  define KEY_W				'w'
#  define KEY_X				'x'
#  define KEY_Y				'y'
#  define KEY_Z				'z'
#  define KEY_LEFT			65361
#  define KEY_RIGHT			65363
#  define KEY_UP			65362
#  define KEY_DOWN			65364
#  define KEY_ENTER			65293
#  define KEY_ESC			65307
#  define KEY_LCTRL			65507
#  define KEY_SPACE			32
#  define KEY_LEFT_CLICK	1
#  define KEY_RIGHT_CLICK	3
# endif

# include <stdio.h>
# include <fcntl.h>
# include <math.h>
# include <stdlib.h>
# include <ctype.h>
# include <stdbool.h>
# include <time.h>
# include "../libft/libft.h"
# include <sys/time.h>
# include <pthread.h>

# define WIN_WIDTH 1280
# define WIN_HEIGHT 1080

# ifndef NUM_THREADS
#  define NUM_THREADS 10
# endif

# define MAP_WALL 0xFFb08243
# define MAP_EMPTY 0xFFdeda68

# define MOVE_SPEED 3.0
# define ROT_SPEED 2.0
// # define JUMP_VEL 8.0
// # define GRAVITY 20.0
// # define MAX_HEIGHT 
// 	(JUMP_VEL * JUMP_VEL / (2.0 / GRAVITY))
// # define JUMP_VIEW_SCALE 30.0

# define TILE_SIZE 1

extern const char	*g_digit[10];

typedef enum e_state
{
	STATE_MENU,
	STATE_PLAY
}	t_state;

typedef enum e_anim
{
	IDLE,
	SHOOT,
	RELOAD
}	t_anim;

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

typedef struct s_img
{
	void	*img;
	t_vec2i	size;
	char	*addr;
	int		bpp;
	int		len;
	int		end;
}	t_img;

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
	int		near_door;
	int		door_x;
	int		door_y;
}	t_player;

typedef struct s_map
{
	int		sizex;
	int		sizey;
	int		screenx;
	int		screeny;
	t_vec2	t_size;
	char	**map;
	bool	**explored;
	char	orientation;
	double	playerx;
	double	playery;
	int		tmp_x;
	int		tmp_y;
}	t_map;

typedef struct s_tex
{
	char	*n;
	char	*s;
	char	*we;
	char	*ea;
	char	f[7];
	int		floor;
	char	c[7];
	int		ceiling;
	int		full;
}	t_tex;

typedef struct s_hud
{
	t_anim	anim_state;
	int		current_frame;
	double	frame_timer;
	double	frame_duration;
	int		frame_count;
	t_img	anim_idle;
	t_img	*anim_shoot;
	t_img	*anim_reload;
}	t_hud;

typedef struct s_cub
{
	void		*mlx;
	void		*mlx_win;
	t_img		back;
	t_player	player;
	t_map		*map;
	t_tex		tex;
	int			debug;
	bool		keys[70000];
	double		frame_time;
	double		delta;
	int			fps;
	t_state		state;
	int			menu_sel;
	int			ismap;
	t_img		north;
	t_img		east;
	t_img		south;
	t_img		west;
	t_hud		hud;
}	t_cub;

/**
 * @brief raycasting structure
 * @param cam_x X-coorinate in cameraspace.
 * Ranges from -1 (left of screen) to 1 (right of screen).
 * Used to calculate ray direction based on the players's field of view.
 * @param ray_dir The direction the ray is pointing in world space.
 * Calculated form s_player's direction and cam_x.
 * @param map The map square the ray is currently in. Used for DDA traversal.
 * @param side_dist Distance from the ray origin to
 * the first x- or y-side it will hit.
 * @param delta_dis Distance the ray must travel to go from one side of a
 * square to the next x or y.
 * @param step Direction to step in the grid: -1 or +1 depending on ray_dir.
 * E.g, if ray_dir.x < 0 -> step.x = -1;
 * @param hit A flag that becomes tru when the ray hits a wall.
 * Ends the DDA loop.
 * @param side Which side of the wall was hit:
 * 0 = vertical (x-side), 1 = horisontal (y-side).
 * @param perp_dist Distance from player to wall hit, adjusted to remove
 * the fish-eye effect. Used to scale the heigh of the wall slice.
 * @param line_h Heigh of the vertical stripe to draw on screen,
 * based on perp_dist.
 * @param draw_start Top pixel (y) of the wall slice to draw.
 * @param draw_end Bottome pixel (y) of the wall slice to draw.
 * @param color Color of teh wall to draw (based on side or texture).
 */
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

typedef struct s_thrdata
{
	t_cub	*cub;
	t_img	*img;
	int		x_start;
	int		x_end;
}	t_thrdata;

typedef struct s_mapdata
{
	t_cub	*cub;
	t_img	img;
}	t_mapdata;

typedef struct s_spawn_args
{
	t_cub		*cub;
	t_img		*back;
	int			slice;
	pthread_t	*threads;
	t_thrdata	*td;
}	t_spawn_args;

/* init */
double			gettime(void);
t_map			*ini_map(t_cub *cub, char **v);
int				init(t_cub *cub, char **v);
void			init_player(t_player *player, t_map *map);
void			init_hud(t_cub *cub, t_hud *hud);

/* mlx */
int				get_pixel(t_img *img, t_vec2 pos);
t_img			make_image(t_cub *cub, t_vec2 size, int color);
t_img			setup_xpm(t_cub *c, char *xpm);
t_vec2			get_rotated_position(t_vec2 center,
					t_vec2 local, double angle);
t_vec2			rotate_point(t_vec2 rel, double angle);
void			draw_line(t_img *img, t_vec2 start, t_vec2 end, int color);
void			draw_pixels(t_img *img, t_vec2 pos, t_vec2 size, int color);
void			draw_rotated_image(t_img *t, t_img *s, t_vec2 pos, double ang);
void			drawtoimg(t_img *src, t_img *dst, t_vec2 pos);
void			mlx_set_img(t_img *img, unsigned int color);
void			my_mlx_pixel_put(t_img *data, int x, int y, int color);
void			draw_image_transparent(t_img *src, t_img *dst, t_vec2 pos);
void			draw_rect(t_img *im, t_vec2 orig, t_vec2 size, int color);
t_img			scale_size(t_cub *cub, t_img img, double scale);

/* player */
int				handle_input(int keycode, t_cub *cub);
int				handle_keyrelease(int kc, t_cub *cub);
void			move_backward(t_player *p, t_map *m, double spd);
void			move_forward(t_player *p, t_map *m, double spd);
void			move_left(t_player *p, t_map *m, double spd);
void			move_right(t_player *p, t_map *m, double spd);
void			rotate(t_player *p, double angle);
void			smooth_input(t_cub *cub);
int				mouse_move(int x, int y, t_cub *cub);
int				mouse_press_handler(int button, int x, int y, void *param);
void			set_anim_state(t_cub *cub, int state);
void			center_mouse(t_cub *cub);

/* render */
int				handle_menu(int key, t_cub *c);
int				render(t_cub *cub);
int				update(t_cub *cub);
t_vec2i			set_raydir(t_raycast *ray);
void			cast_rays(t_cub *cub, t_img *img, int x_start, int x_end);
void			change_debug(t_cub *cub);
void			draw_big_fps(t_cub *cub);
void			draw_debug(t_cub *cub);
void			draw_debug_rays(t_cub *c, t_img *m, t_vec2 pos);
void			draw_digit(t_cub *c, char d, t_vec2i oi, int s);
void			draw_dir(t_player *p, t_vec2 map_pos, t_img *map);
void			draw_menu(t_cub *c);
void			draw_player(t_cub *cub, t_player *player, t_img *map);
void			draw_px(t_cub *c, int x, int y);
void			init_ray(t_cub *cub, t_raycast *ray, int x);
void			perform_dda(t_raycast *ray, t_cub *cub);
void			*render_map(t_cub *cub, t_img *img, t_player *player);
void			set_side_dist(t_raycast *ray, t_player player);
void			draw_texture(t_cub *c, t_img *img, t_raycast *ray, int x);
void			draw_stripe(t_raycast *ray);
void			open_xpm(t_cub *c);
void			*render_thread(void *arg);
void			*render_map_thread(void *arg);
void			set_bg(t_img *back, t_cub *c);
void			init_back_buffer(t_cub *cub, t_img *back);
void			create_map_thread(t_cub *cub, pthread_t *thread, t_mapdata *md);
void			finalize_back_buffer(t_cub *cub, t_img *back);
void			join_threads(pthread_t *threads, int count);
void			init_minimap(t_cub *c, t_map *m, t_img *map);
void			draw_hud(t_cub *cub, t_img *dst);
void			reveal_surr(t_map *map, t_vec2 pos, int radius);
bool			is_tile_visible(t_map *m, t_vec2 pl_pos, t_vec2i tile);

/* utils */
int				close_window(t_cub *cub);
int				is_in_bounds(t_img *img, t_vec2 point);
t_vec2			fix_pos(t_cub *cub, t_img *dst, t_vec2 pos);
t_vec2			get_center(t_img *img);
t_vec2			set_vec2(double x, double y);
t_vec2			vec2_add(t_vec2 vec1, t_vec2 vec2);
t_vec2			vec2_div(t_vec2 vec1, t_vec2 vec2);
t_vec2			vec2_mult(t_vec2 vec1, t_vec2 vec2);
t_vec2			vec2_sub(t_vec2 vec1, t_vec2 vec2);
t_vec2i			vecdtoi(t_vec2 vec2);
t_vec3			set_vec3(double x, double y, double z);
t_vec4			set_vec4(int r, int g, int b, int a);
t_vec2i			set_vec2i(int x, int y);
t_vec2			itovec(t_vec2i veci);
void			free_all(t_cub *c);
t_spawn_args	setup_args(t_cub *c, t_img *back, pthread_t *threads,
					t_thrdata *td);

void			near_to_door(t_raycast ray, t_cub *c);
#endif
