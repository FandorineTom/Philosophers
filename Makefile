# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: snorthmo <snorthmo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/02/28 13:16:56 by snorthmo          #+#    #+#              #
#    Updated: 2021/03/04 00:29:03 by snorthmo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo_one
SRC = philo_one.c ft_utils.c inits.c philo_doing_smth.c
OBJ = $(SRC:.c=.o)
HEADER = ./
FLAGS = -g -Wall -Werror -Wextra

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJ)
	gcc $(OBJ) -o $(NAME)

%.o: %.c $(HEADER)philo_one.h
	gcc -c $< -o ${<:.c=.o} -I $(HEADER)

clean:
	/bin/rm -f $(OBJ)

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all
