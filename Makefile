CC = cc

CFLAGS = -Werror -Wall -Wextra -I.

NAME = fdf

SRCS = fdf.c

OBJS = $(SRCS:.c=.o)

MLX_PATH = ./mlx_linux
MLX_NAME = $(MLX_PATH)/libmlx.a
MLX_FLAGS = -lXext -lX11 -lm -lz

# LIBFT = $(LIBFT_DIR)/libft.a
# LIBFT_DIR = LIBFT_DIR

all: $(MLX_NAME) $(NAME)

# $(NAME): $(OBJS) $(LIBFT)
# 	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)

$(MLX_NAME):
	make -C $(MLX_PATH)

$(NAME): $(OBJS) $(MLX_NAME)
	$(CC) $(OBJS) -L$(MLX_PATH) -lmlx $(MLX_FLAGS) -o $(NAME)

%.o: %.c
# $(CC) $(CFLAGS) -c $< -o $@
	$(CC) $(CFLAGS) -I$(MLX_PATH) -O3 -c $< -o $@

clean:
	rm -f $(OBJS)
	make -C $(MLX_PATH) clean

fclean: clean
	rm -f $(NAME)
	make -C $(MLX_PATH) clean

re: fclean all

.PHONY: all clean fclean re