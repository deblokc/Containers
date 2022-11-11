# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tnaton <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/22 19:13:09 by tnaton            #+#    #+#              #
#    Updated: 2022/11/11 14:17:51 by tnaton           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = test

SRC = main.cpp

INC = vector.hpp viterator.hpp iterator_traits.hpp stack.hpp

OBJ = $(SRC:.cpp=.o)

CXX = c++

CXXFLAGS = -Wall -Wextra -Werror -Wpedantic -g -std=c++98

$(NAME): $(OBJ)
	$(CXX) $(CXXFLAGS) -D NAMESPACE=FT $(OBJ) -o $@

$(OBJ): $(INC)

all: $(NAME)
.PHONY: all

clean:
	rm -rf $(OBJ)
.PHONY: clean

fclean: clean
	rm -rf $(NAME)
.PHONY: fclean

re: fclean all
.PHONY: re

.SECONDARY : $(OBJ)
