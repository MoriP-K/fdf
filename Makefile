CC = cc

CFLAGS = -Wall -Wextra -Werror -I. -I$(MLX_PATH) -I$(LIBFT_DIR)

NAME = fdf

SRCS = gnl/get_next_line.c \
		draw_line.c \
		draw_map_1.c \
		draw_map_2.c \
		end_fdf.c \
		fdf.c \
		free_fdf.c \
		init_1.c \
		init_2.c \
		init_map_1.c \
		init_map_2.c \
		instructions.c \
		read_map.c \
		utils.c \

OBJS = $(SRCS:.c=.o)

MLX_PATH = ./minilibx-linux
MLX_NAME = $(MLX_PATH)/minilibx.a
MLX_FLAGS = -lXext -lX11 -lm -lz

LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

all: $(MLX_NAME) $(LIBFT) $(NAME)

$(MLX_NAME):
	make -C $(MLX_PATH)

$(LIBFT):
	make -C $(LIBFT_DIR)

$(NAME): $(OBJS) $(MLX_NAME) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) -L$(MLX_PATH) -lmlx $(MLX_FLAGS) -L$(LIBFT_DIR) -lft -o $(NAME)

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

.PHONY: all clean fclean re rr bonus