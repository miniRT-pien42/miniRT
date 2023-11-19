PROG := result

CC := cc
CFLAGS := -Wall -Wextra -Werror
SRCS =	shade_add_floor.c\
		../utils/ray.c\
		../utils/vector.c

OBJS := $(SRCS:.c=.o)

$(PROG): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

all: $(PROG)

clean:
	rm -f $(OBJS)

fclean:	clean
	rm -f $(PROG)

re:	fclean all

.PHONY:	all clean fclean re