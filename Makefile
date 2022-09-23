# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tnaton <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/22 19:13:09 by tnaton            #+#    #+#              #
#    Updated: 2022/09/23 20:36:41 by tnaton           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = test

SRC = main.cpp

INC = vector.hpp iterator.hpp iterator_traits.hpp stack.hpp

OBJ = $(SRC:.cpp=.o)

CXX = c++

CPPFLAGS = -Wall -Wextra -Werror -g -std=c++98

$(NAME): $(OBJ)
	$(CXX) $(CPPFLAGS) $(OBJ) -o $@

$(OBJ): $(INC)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.SECONDARY : $(OBJ)
