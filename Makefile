CC = cc
# CFLAGS = -g# -fsanitize=address#temp
CFLAGS = -Wall -Wextra -Werror

SRCS_DIR = srcs
SRCS = $(addprefix $(SRCS_DIR)/, main.c parse.c rendering_setup.c hooks.c draw.c memory.c split.c trim.c utils.c) # to be updated

OBJS_DIR = objs
OBJS = $(addprefix $(OBJS_DIR)/, $(notdir $(SRCS:.c=.o)))

HEADERS = -I ./includes -I $(LIBFT_DIR)/includes -I $(LIBMLX42_DIR)/include

UNAME_S	= $(shell uname -s)
ifeq ($(UNAME_S),Linux)
	LIBS = $(LIBFT) $(LIBMLX42) -ldl -lglfw -pthread -lm
endif
ifeq ($(UNAME_S),Darwin)
	LIBS = $(LIBFT) $(LIBMLX42) -lglfw -framework Cocoa -framework OpenGL -framework IOKit
endif
# macOS (the flag for glfw might be with or without a 3 at the end)
# LIBS = $(LIBFT) $(LIBMLX42) -lglfw3 -framework Cocoa -framework OpenGL -framework IOKit
# LIBS = $(LIBFT) $(LIBMLX42) -lglfw -L"/opt/homebrew/Cellar/glfw/3.3.8/lib/" -pthread -lm

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

$(LIBMLX42): $(LIBMLX42_DIR)
	git submodule update --init $(LIBMLX42_DIR)
	cmake $(LIBMLX42_DIR) -B $(LIBMLX42_DIR)/build && make -C $(LIBMLX42_DIR)/build -j4

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c $(LIBMLX42) includes/fdf.h | $(OBJS_DIR)
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
