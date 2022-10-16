SRCS = 	main.c \
		srcs/gnl/get_next_line_utils.c \
		srcs/gnl/get_next_line.c \
		srcs/parser/parse_ambient_lighting.c \
		srcs/parser/parser_utils.c \
		srcs/parser/parser.c \
		srcs/utils/error.c \
		srcs/utils/free.c \
		srcs/utils/get2d_array_size.c \
		srcs/utils/parse_color.c \
		srcs/utils/parse_double.c 

OBJS = ${SRCS:.c=.o}

CC = gcc

CFLAGS = -Wall -Wextra -Werror -g3

OS = $(shell uname)

LIBFT = libs/libft/libft.a

LIBFT_PATH = libs/libft

LIBFT_PATH = libs/libft

ifeq ($(OS), Linux)
	MLX_FLAGS = -Llibs/mlx/linux -lmlx -Ilibs/mlx_linux -lXext -lX11 -lm -lz
	MLX_PATH = libs/mlx/linux
else
	MLX_FLAGS = -Llibs/mlx/mac -lmlx -Ilibs/mlx_mac -framework OpenGL -framework AppKit
	MLX_PATH = libs/mlx/mac
endif

NAME = miniRT

all : $(NAME)

$(NAME) : $(OBJS)
	$(MAKE) -C $(MLX_PATH)
	$(MAKE) -C $(LIBFT_PATH)
	$(MAKE) -C $(LIBFT_PATH) bonus
	$(CC) $(OBJS) $(LIBFT) $(MLX_FLAGS)  $(CFLAGS) -o $(NAME)

clean:
	$(MAKE) clean -C $(MLX_PATH)
	$(MAKE) clean -C $(LIBFT_PATH)
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)
	$(MAKE) clean -C $(MLX_PATH)
	$(MAKE) fclean -C $(LIBFT_PATH)

re : fclean all
