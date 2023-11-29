NAME		:=	libft.a

SRC_DIR		:=	srcs
SRCS		:=	ft_free.c \
				ft_split.c \
				ft_strlcpy_void.c \
				ft_strndup.c \
				ft_strnlen.c \
				x_malloc.c

OBJ_DIR		:=	objs
OBJS		:=	$(SRCS:%.c=$(OBJ_DIR)/%.o)

DEPS		:=	$(OBJS:.o=.d)

INCLUDE_DIR	:=	includes
INCLUDES	:=	-I./$(INCLUDE_DIR)/ -I.

CC			:=	cc
CFLAGS		:=	-Wall -Wextra -Werror -MMD -MP
DEPS		:=	$(OBJS:.o=.d)
MKDIR		:=	mkdir -p

#--------------------------------------------
.PHONY	: all
all		: $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@$(MKDIR) $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(NAME): $(OBJS)
	$(AR) $(ARFLAGS) $(NAME) $(OBJS)

.PHONY	: clean
clean:
	$(RM) -r $(OBJ_DIR)

.PHONY	: fclean
fclean: clean
	$(RM) $(NAME)

.PHONY	: re
re: fclean all

#--------------------------------------------

-include $(DEPS)
