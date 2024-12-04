CC = cc
CFLAGS = -Wall -Wextra -Werror

SRCS_DIR = srcs
SRCS = $(addprefix $(SRCS_DIR)/, main.c ) # to be updated

OBJS_DIR = objs
OBJS = $(addprefix $(OBJS_DIR)/, $(notdir $(SRCS:.c=.o)))

HEADERS = -I ./includes -I $(LIBFT_DIR)/includes -I $(LIBMLX42_DIR)/include

# linux
LIBS = $(LIBFT) $(LIBMLX42) -ldl -lglfw -pthread -lm
# macOS (the flag for glfw might be with or without a 3 at the end)
# LIBS = $(LIBFT) $(LIBMLX42) -lglfw -framework Cocoa -framework OpenGL -framework IOKit

LIBFT_DIR = lib/libft
LIBFT = $(LIBFT_DIR)/libft.a

LIBMLX42_DIR = lib/MLX42
LIBMLX42 = $(LIBMLX42_DIR)/build/libmlx42.a

NAME = fdf

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(LIBMLX42)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)

$(LIBFT):
	make -C $(LIBFT_DIR)

$(LIBMLX42):
	git submodule update --init $(LIBMLX42_DIR)
	cmake $(LIBMLX42_DIR) -B $(LIBMLX42_DIR)/build && make -C $(LIBMLX42_DIR)/build -j4

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c | $(OBJS_DIR)
	$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@

$(OBJS_DIR):
	mkdir -p $@

clean:
	rm -rf $(OBJS_DIR)
	make -C $(LIBFT_DIR) clean
	rm -rf $(LIBMLX42_DIR)/build

fclean: clean
	rm -f $(NAME)
	make -C $(LIBFT_DIR) fclean
	git submodule deinit -f $(LIBMLX42_DIR)

re: fclean all

.PHONY: all clean fclean re
