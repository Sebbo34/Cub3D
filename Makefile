NAME		:= cub3D

SRCS		:=	main.c \
				map.c
OBJS		:= $(SRCS:.c=.o)

SRCS		:= $(addprefix sources/,$(SRCS))
OBJS		:= $(addprefix build/,$(OBJS))

CFLAGS		:= -Wall -Wextra -Werror
CPPFLAGS	:= -Iinclude -Iminilibx-linux
LDFLAGS		:= -lX11 -lXext -Lminilibx-linux -lmlx

all: $(NAME)

build/%.o: sources/%.c
	mkdir -p build
	$(CC) -c $< -o $@ $(CFLAGS) $(CPPFLAGS)

$(NAME): $(OBJS) minilibx-linux/libmlx.a
	$(CC) $(OBJS) $(LDFLAGS) -o $(NAME)

minilibx-linux/libmlx.a:
	$(MAKE) -C minilibx-linux

clean:
	rm -rf build

fclean: clean
	rm -f $(NAME)

re:
	$(MAKE) fclean
	$(MAKE) all

.PHONY: all clean fclean re