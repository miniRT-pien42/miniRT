NAME		:=	minirt

SRC_DIR		:=	srcs
SRCS		:=	display.c \
				error.c \
				init.c \
				main.c \
				sphere.c \
				utils.c \
				vector.c

OBJ_DIR		:=	objs
OBJS		:=	$(SRCS:%.c=$(OBJ_DIR)/%.o)

DEPS		:=	$(OBJS:.o=.d)

LIBFT_DIR	:=	libft
LIBFT		:=	$(LIBFT_DIR)/libft.a

MLX_DIR		:=	minilibx
MLX_FLAGS	:=	-Lmlx_linux -lXext -lX11 -lm
MINILIBX	:=	$(MLX_DIR)/libmlx_Linux.a

INCLUDE_DIR	:=	includes
INCLUDES	:=	-I./$(INCLUDE_DIR)/ -I$(LIBFT_DIR)/$(INCLUDE_DIR)/ -I$(MLX_DIR)/ -I.

CC			:=	cc
CFLAGS		:=	-Wall -Wextra -Werror -MMD -MP
DEPS		:=	$(OBJS:.o=.d)
MKDIR		:=	mkdir -p

#--------------------------------------------
.PHONY	: all
all		: $(NAME)

# .PHONY	: bonus
# bonus	: all

# $(LIBFT): FORCE
# 	$(MAKE) -C $(LIBFT_DIR)

$(MINILIBX):
	$(MAKE) -C $(MLX_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@$(MKDIR) $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(NAME): $(OBJS) $(LIBFT) $(MINILIBX)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LIBFT) $(MINILIBX) $(MLX_FLAGS)

.PHONY	: clean
clean:
	$(RM) -r $(OBJ_DIR) $(LIBFT_DIR)/$(OBJ_DIR)

.PHONY	: fclean
fclean: clean
	$(RM) $(NAME) $(LIBFT)

.PHONY	: re
re: fclean all

.PHONY	: clone
clone:
	git clone https://github.com/42Paris/minilibx-linux $(MLX_DIR)

.PHONY	: norm
norm:
	python3 test/norm.py

FORCE:

#--------------------------------------------

-include $(DEPS)
