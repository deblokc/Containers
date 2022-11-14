# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tnaton <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/22 19:13:09 by tnaton            #+#    #+#              #
#    Updated: 2022/11/14 19:25:55 by tnaton           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FT = test_ft

STD = test_std

SRC = main.cpp

INC = vector.hpp viterator.hpp iterator_traits.hpp stack.hpp

OBJ = $(SRC:.cpp=.o)

PREC = 1

CXX = c++

CXXFLAGS = -Wall -Wextra -Werror -Wpedantic -g -std=c++98

all: $(FT) $(STD)
.PHONY: all

$(FT): $(SRC)
	$(CXX) $(CXXFLAGS) -DNAMESPACE=ft -DPREC=$(PREC) $(SRC) -o $@
	
$(STD): $(SRC)
	$(CXX) $(CXXFLAGS) -DNAMESPACE=std -DPREC=$(PREC) $(SRC) -o $@

$(OBJ): $(INC)

clean:
	rm -rf $(OBJ) ft.log std.log
.PHONY: clean

fclean: clean
	rm -rf $(FT) $(STD)
.PHONY: fclean

test: $(FT) $(STD)
	sh test.sh
.PHONY: test

re: fclean all
.PHONY: re

.SECONDARY : $(OBJ)
