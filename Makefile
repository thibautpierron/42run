# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tpierron <tpierron@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/07/21 11:32:23 by tpierron          #+#    #+#              #
#    Updated: 2017/09/11 11:46:58 by tpierron         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all clean fclean re

NAME = 42Run

CC = clang++
SRC =	classes/Shader.class.cpp \
		classes/model/Mesh.class.cpp \
		classes/model/Model.class.cpp	\
		classes/model/Joint.class.cpp	\
		classes/game/Area.class.cpp	\
		classes/game/Player.class.cpp	\
		classes/game/Game.class.cpp	\
		main.cpp \
		sdl_tools.cpp

CFLAGS = -Wall -Wextra -Werror
OBJ_PATH = ./obj/
OBJ_NAME = $(SRC:.cpp=.o)

SDL = -L/Users/tpierron/.brew/lib -lSDL2
SDL_PATH = -I/Users/tpierron/.brew/include/SDL2

ASSIMP = -L/Users/tpierron/.brew/lib -lassimp
ASSIMP_PATH = -I/Users/tpierron/.brew/include/

STB = -Ilibs/stb/

OPENGL = -framework OpenGl -framework AppKit

OBJ = $(addprefix $(OBJ_PATH), $(OBJ_NAME))

all: $(NAME)
$(OBJ_PATH)%.o: %.cpp
	@mkdir $(OBJ_PATH) 2> /dev/null || echo "" > /dev/null
	@mkdir $(OBJ_PATH)/classes 2> /dev/null || echo "" > /dev/null
	@mkdir $(OBJ_PATH)/classes/model 2> /dev/null || echo "" > /dev/null
	@mkdir $(OBJ_PATH)/classes/game 2> /dev/null || echo "" > /dev/null
	$(CC) $(CFLAGS) -o $@ -c -Iclasses -Iclasses/model $(SDL_PATH) $(ASSIMP_PATH) $< -std=c++11

$(NAME): $(OBJ)
	$(CC) $(SDL) $(ASSIMP) $(OPENGL) $(CFLAGS) -o $@ $^

clean:
	rm -rf $(OBJ_PATH)

fclean: clean
	rm -f $(NAME)

re: fclean all
