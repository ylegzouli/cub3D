.PHONY: all clean fclean re norme

CC = gcc

FLAGS = -Wall -Wextra -Werror

CPP_FLAGS = -Iinclude

NAME = Cub3D

SRC_PATH = ./src
LIB_PATH = ./lib
INC_PATH = ./include
OBJ_PATH = ./obj
OBJLIB_PATH = ./obj

SRC_NAME =	start.c affichage.c event.c init.c parsing.c \
            bmp.c image.c other.c raycast.c texture.c

LIB_NAME = ft_atoi.c ft_bzero.c ft_lstadd_back.c ft_lstclear.c \
                ft_lstnew.c ft_memcpy.c ft_split.c ft_strcpy.c ft_strjoin.c \
                ft_strlen.c ft_strncmp.c ft_substr.c get_next_line.c \
                ft_memset.c \

INC_NAME = cub3D.h

OBJ_NAME = $(SRC_NAME:.c=.o)
OBJLIB_NAME = $(LIB_NAME:.c=.o)

SRC = $(addprefix $(SRC_PATH)/, $(SRC_NAME))
LIB = $(addprefix $(LIB_PATH)/, $(LIB_NAME))
INC = $(addprefix $(INC_PATH)/, $(INC_NAME))
OBJ = $(addprefix $(OBJ_PATH)/,$(OBJ_NAME))
OBJLIB = $(addprefix $(OBJLIB_PATH)/,$(OBJLIB_NAME))

all: $(NAME)

$(NAME): $(OBJ) $(OBJLIB)
	gcc -Wall -Wextra -Werror -o ${NAME} /usr/local/lib/libmlx.a ${OBJLIB} -l mlx -framework OpenGL -framework AppKit ${OBJ}

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	mkdir $(OBJ_PATH) 2> /dev/null || true
	$(CC) -o $@ -c $<

$(OBJLIB_PATH)/%.o: $(LIB_PATH)/%.c
	mkdir $(OBJLIB_PATH) 2> /dev/null || true
	$(CC) -o $@ -c $<

clean:
	rm -rf $(OBJ) $(OBJLIB)

fclean: clean
	rm -rf ./obj $(NAME)

re: fclean all

norme:
	@norminette $(SRC) $(LIB) $(INC)
