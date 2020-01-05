SRCS_cub3d =	src/affichage.c src/event.c src/init.c src/parsing.c src/start.c \
				src/bmp.c src/image.c src/other.c src/raycast.c src/texture.c

SRCS_libft = 	lib/ft_atoi.c lib/ft_bzero.c lib/ft_lstadd_back.c lib/ft_lstclear.c \
				lib/ft_lstnew.c lib/ft_memcpy.c lib/ft_split.c lib/ft_strcpy.c lib/ft_strjoin.c \
				lib/ft_strlen.c lib/ft_strncmp.c lib/ft_substr.c lib/gnl/get_next_line.c \
				lib/ft_memset.c \
SRCS = ${SRCS_cub3d} ${SRCS_libft}

INCL = -Iincludes/

OBJS = ${SRCS:.c=.o}

NAME = Cub3D

FLAGS = -Wall -Wextra -Werror

all : $(NAME)

$(NAME) : ${OBJS}
		gcc  ${FLAGS} -I/usr/local/include -o$(NAME) ${OBJS} lib/libmlx.a -L/usr/local/lib -lmlx -framework Opengl -framework APPKIT

.c.o : ${SRCS}
		gcc ${FLAGS} -c ${INCL} $< -o ${<:.c=.o}
clean :
		rm -f ${OBJS}

fclean : clean
		rm -f $(NAME)

re : fclean
		make all

.PHONY: all clean fclean re
