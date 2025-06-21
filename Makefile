#───────────────────────────  PROJECT BASICS  ────────────────────────────────#
NAME = cub3d
CC   = cc
INC = include
RM   = rm -rf
FLAGS = -Werror -Wextra -Wall -g -I$(INC) #-fsanitize=address
MAKE := make --no-print-directory

#────────────────────────────  LIBFT SECTION  ────────────────────────────────#
LIBFT_A   = libft.a
LIBFT_DIR = libft/
LIBFT     = $(addprefix $(LIBFT_DIR), $(LIBFT_A))
PRINTF    = $(addprefix $(PRINTF_DIR), $(PRINTF_A))

#───────────────────────────  MINILIBX SECTION  ──────────────────────────────#
OS = $(shell uname)

ifeq ($(OS),Darwin)                # ▸▸ macOS
	MLX_DIR   = mlx_mac
	MLX_INC   := -I$(MLX_DIR)
	MLX_LIBS  := -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit
	MLX       = $(MLX_DIR)/libmlx.a
else                                # ▸▸ Linux (42 VM, WSL, etc)
	MLX_DIR   = mlx_linux
	MLX_INC   := -I$(MLX_DIR)
	MLX_LIBS  := -L$(MLX_DIR) -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz
	MLX       = $(MLX_DIR)/libmlx_Linux.a
endif

#--------------------------------------SOURCES---------------------------------#
SRC_DIR = src/
SRC_SRC =  \
	main.c
SRC = $(addprefix $(SRC_DIR), $(SRC_SRC))

INIT_DIR = src/init/
INIT_SRC =  \
	init.c \
	init_hud.c
INIT = $(addprefix $(INIT_DIR), $(INIT_SRC))

MLX_DIR = src/mlx/
MLX_SRC =  \
	draw.c \
	draw2.c \
	mlx_helper.c \
	mlx_helper2.c
MLX = $(addprefix $(MLX_DIR), $(MLX_SRC))

PARSING_DIR = src/parsing/
PARSING_SRC =  \
	free_texture.c \
	handle_map.c \
	init_map.c \
	init_texture.c \
	open_files.c \
	rescale_map.c \
	utils.c
PARSING = $(addprefix $(PARSING_DIR), $(PARSING_SRC))

PLAYER_DIR = src/player/
PLAYER_SRC =  \
	input.c \
	move.c \
	move2.c
PLAYER = $(addprefix $(PLAYER_DIR), $(PLAYER_SRC))

RENDER_DIR = src/render/
RENDER_SRC =  \
	debug.c \
	debug_rays.c \
	font.c \
	menu.c \
	ray_utils.c \
	rays.c \
	render.c \
	texture.c \
	update.c \
	doors.c
RENDER = $(addprefix $(RENDER_DIR), $(RENDER_SRC))

ANIM_DIR = src/render/anim/
ANIM_SRC =  \
	draw_hud.c
ANIM = $(addprefix $(ANIM_DIR), $(ANIM_SRC))

MAP_DIR = src/render/map/
MAP_SRC =  \
	map.c \
	map_fog.c
MAP = $(addprefix $(MAP_DIR), $(MAP_SRC))

UTILS_DIR = src/utils/
UTILS_SRC =  \
	close.c \
	img_math.c \
	map_math.c \
	math_vec.c \
	util_vec.c \
	util_veci.c
UTILS = $(addprefix $(UTILS_DIR), $(UTILS_SRC))

ALL_SRC = $(SRC) $(INIT) $(MLX) $(PARSING) $(PLAYER) $(RENDER) $(ANIM) $(MAP) $(UTILS)
vpath %.c src src/init src/mlx src/parsing src/player src/render src/render/anim src/render/map src/utils
#--------------------------------------OBJECTS----------------------------------#
OBJ_DIR  = Objects/
OBJECTS  = $(patsubst %.c,$(OBJ_DIR)%.o,$(notdir $(ALL_SRC)))
VPATH    = $(SRC_DIR):$(INIT_DIR):$(CMDS_DIR):$(PARS_DIR):$(EXEC_DIR):$(BEF_DIR)

#────────────────────────────  ANIMATION CONFIG  ─────────────────────────────#
ANIMATION_FRAMES = ⠋ ⠙ ⠹ ⠸ ⠼ ⠴ ⠦ ⠧ ⠇ ⠏
ANIMATION_COLOR  = '\033[1;36m'
TOTAL_FILES := $(words $(OBJECTS))

#───────────────────────────────  COLOR CODES  ───────────────────────────────#
NONE='\033[0m'
GREEN='\033[32m'
YELLOW='\033[33m'
GRAY='\033[2;37m'
CURSIVE='\033[3m'
BLUE='\033[34m'
MAGENTA='\033[35m'
CYAN='\033[36m'
WHITE='\033[37m'
BOLD='\033[1m'

#────────────────────────────────  RULES  ─────────────────────────────────────#
all: reset_counter $(OBJ_DIR) $(LIBFT) $(NAME)

reset_counter:
	@rm -f .counter
	@echo "0" > .counter

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
	@echo $(BOLD)$(MAGENTA)"Objects directory created"$(NONE)

$(LIBFT):
	@echo $(CURSIVE)$(GRAY)"🔧 Making libft..."$(NONE)
	@$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(MLX) $(OBJECTS)
	@$(CC) $(FLAGS) $(OBJECTS) $(LIBFT) $(PRINTF) $(MLX_LIBS) -o $(NAME)
	@echo "\033[1;32m\n✅ $(NAME) successfully compiled!\n\033[0m"
	@rm .counter

#────────────────────────────  COMPILATION RULE  ─────────────────────────────#
$(OBJ_DIR)%.o: %.c
	@mkdir -p $(OBJ_DIR)
	@if [ ! -f .counter ]; then echo "0" > .counter; fi
	@file_count=$$(cat .counter); \
	file_count=$$((file_count + 1)); \
	echo $$file_count > .counter; \
	frames="⠋ ⠙ ⠹ ⠸ ⠼ ⠴ ⠦ ⠧ ⠇ ⠏"; \
	frame_index=$$((file_count % 10)); \
	frame=$$(echo $$frames | cut -d ' ' -f $$((frame_index + 1))); \
	percent=$$((100 * file_count / $(TOTAL_FILES))); \
	barlen=30; \
	done=$$((barlen * percent / 100)); \
	todo=$$((barlen - done)); \
	bar=$$(printf "█%.0s" $$(seq 1 $$done)); \
	space=$$(printf "░%.0s" $$(seq 1 $$todo)); \
	printf "\r\033[1;36m%s \033[1mCompiling\033[0m [%-*s] %3d%% \033[36m%-40.40s\033[0m" "$$frame" "$$barlen" "$$bar$$space" "$$percent" "$<"; \
	$(CC) $(FLAGS) -I $(MLX_INC) -c $< -o $@

clean:
	@echo $(CURSIVE)$(GRAY)" -> Cleaning object files.."$(NONE)
	@$(RM) $(OBJ_DIR)
	@$(RM) .counter
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	@echo $(CURSIVE)$(GRAY)" -> Removing $(NAME)"$(NONE)
	@$(RM) $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

bonus:
	@echo $(CURSIVE)$(GRAY)" - Compiling bonus $(NAME)..."$(NONE)
	@echo $(GREEN)"- Compiled -"$(NONE)

.PHONY: all clean fclean re bonus reset_counter
