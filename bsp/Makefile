NAME = bsp
CC   = cc
INC  = include
RM   = rm -rf
FLAGS = -Werror -Wextra -Wall -g -I$(INC)
MAKE := make --no-print-directory

# Libft
LIBFT_DIR = libft/
LIBFT_A   = libft.a
LIBFT     = $(addprefix $(LIBFT_DIR), $(LIBFT_A))

# Répertoires et fichiers source
SRC_DIR  = src/
SRC_SRC  = \
	main.c \
	gen_map.c \
	bsp.c 

SRC      = $(addprefix $(SRC_DIR), $(SRC_SRC))
OBJ      = $(SRC:.c=.o)

# Cible par défaut
all: $(NAME)

# Compilation du programme
$(NAME): $(LIBFT) $(OBJ)
	$(CC) $(FLAGS) -o $@ $(OBJ) -L$(LIBFT_DIR) -lft -lm

# Compilation des .o
$(SRC_DIR)%.o: $(SRC_DIR)%.c
	$(CC) $(FLAGS) -c $< -o $@

# Compilation de la libft
$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

# Nettoyage des objets
clean:
	$(RM) $(OBJ)
	@$(MAKE) -C $(LIBFT_DIR) clean

# Nettoyage complet
fclean: clean
	$(RM) $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean

# Recompilation totale
re: fclean all

.PHONY: all clean fclean re
