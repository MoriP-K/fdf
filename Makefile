CC = cc

CFLAGS = -Werror -Wall -Wextra -I. -I$(MLX_PATH) -I$(LIBFT_DIR) -fsanitize=undefined -g

NAME = fdf

SRCS = fdf_new.c gnl/get_next_line.c

OBJS = $(SRCS:.c=.o)

MLX_PATH = ./minilibx-linux
MLX_NAME = $(MLX_PATH)/minilibx.a
MLX_FLAGS = -lXext -lX11 -lm -lz

LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

all: $(MLX_NAME) $(LIBFT) $(NAME)

$(NAME): $(OBJS) $(MLX_NAME) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) -L$(MLX_PATH) -lmlx $(MLX_FLAGS) -L$(LIBFT_DIR) -lft -o $(NAME)

$(MLX_NAME):
	make -C $(MLX_PATH)

$(LIBFT):
	make -C $(LIBFT_DIR)

%.o: %.c fdf.h gnl/get_next_line.h
	$(CC) $(CFLAGS) -O3 -c $< -o $@

clean:
	rm -f $(OBJS)
	make -C $(MLX_PATH) clean
	make -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	rm -f $(LIBFT)
	make -C $(MLX_PATH) clean
	make -C $(LIBFT_DIR) clean

re: fclean all

rr:
	make re && make clean

bonus: all
# bonus用に全ファイルに"_bonus"をつけたファイルを作成する

.PHONY: all clean fclean re rr bonus