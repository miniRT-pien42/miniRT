NAME		:=	miniRT

SRC_DIR		:=	srcs
SRCS		:=	cylinder/cylinder_ray.c \
				cylinder/cylinder.c \
				vec/vector1.c \
				vec/vector2.c \
				vec/vector3.c \
				vec/quaternion.c \
				helpers/helpers_math1.c \
				error/error.c \
				scene/scene.c \
				ray/ray.c \
				camera/camera.c \
				light/light.c \
				object/object.c \
				object/distance.c \
				plane/plane.c \
				plane/plane_ray.c \
				sphere/sphere.c \
				sphere/sphere_ray.c \
				sphere/sphere_color.c \
				display/init.c \
				display/display.c \
				display/set_each_pixel.c \
				debug/debug.c \
				debug/print_object.c \
				debug/print_rt_file.c \
				parser/check_file_path.c \
				parser/check_lines.c \
				parser/check_scene_value.c \
				parser/convert_lines_to_scene.c \
				parser/convert.c \
				parser/is_correct_blocks.c \
				parser/is_correct_value_count.c \
				parser/is_unique.c \
				parser/parse.c \
				parser/read.c \
				main.c

OBJ_DIR		:=	objs
OBJS		:=	$(SRCS:%.c=$(OBJ_DIR)/%.o)

DEPS		:=	$(OBJS:.o=.d)

LIBFT_DIR	:=	libft
LIBFT		:=	$(LIBFT_DIR)/libft.a

MLX_DIR		:=	minilibx

INCLUDE_DIR	:=	includes
INCLUDES	:=	-I./$(INCLUDE_DIR)/ -I$(LIBFT_DIR)/$(INCLUDE_DIR)/ -I$(MLX_DIR)/ -I.

OS_TYPE := $(shell uname -s)
ifeq ($(OS_TYPE),Darwin)
	MLX_FLAGS	:=	-L/opt/X11/lib -lXext -lX11 -framework OpenGL -framework AppKit
	MINILIBX	:=	$(MLX_DIR)/libmlx_Darwin.a
	INCLUDES	+=	-I/opt/X11/include -Iminilibx
else
	MLX_FLAGS	:=	-Lmlx_linux -lXext -lX11 -lm
	MINILIBX	:=	$(MLX_DIR)/libmlx_Linux.a
endif

CC			:=	cc
CFLAGS		:=	-Wall -Wextra -Werror -MMD -MP
DEPS		:=	$(OBJS:.o=.d)
MKDIR		:=	mkdir -p

#--------------------------------------------
.PHONY	: all
all		: $(NAME)

# .PHONY	: bonus
# bonus	: all

$(LIBFT): FORCE
	$(MAKE) -C $(LIBFT_DIR)

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
