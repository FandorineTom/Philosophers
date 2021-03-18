# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: snorthmo <snorthmo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/02/28 13:16:56 by snorthmo          #+#    #+#              #
#    Updated: 2021/03/15 15:27:22 by snorthmo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo_three
SRC = philo_three.c ft_utils_three.c inits_three.c philo_doing_smth_three.c
OBJ = $(SRC:.c=.o)
HEADER = ./
FLAGS = -g -Wall -Werror -Wextra -pthread

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJ)
	gcc $(FLAGS) $(OBJ) -o $(NAME)

%.o: %.c $(HEADER)philo_three.h
	gcc -c $(FLAGS) $< -o ${<:.c=.o} -I $(HEADER)

clean:
	/bin/rm -f $(OBJ)

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all
