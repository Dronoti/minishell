# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bkael <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/14 12:11:53 by bkael             #+#    #+#              #
#    Updated: 2021/11/14 19:00:30 by bkael            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

HEADER = srcs/minishell.h

SRC = srcs/env.c \
	srcs/errors.c \
	srcs/join.c \
	srcs/main.c \
	srcs/parser.c \
	srcs/redirect.c \
	srcs/signals.c \
	srcs/start_exec.c \
	srcs/tokens.c \
	srcs/utils.c \
	srcs/utils2.c \
	srcs/utils3.c \

OBJ = $(SRC:%.c=%.o)

FLAGS = -Wall -Wextra -Werror -I ./readline/8.1.1/include

READLINE = -lreadline -L ./readline/8.1.1/lib

all: $(NAME)

$(NAME): $(OBJ)
	gcc $(FLAGS) $(READLINE) $^ -o $(NAME)

%.o: %.c $(HEADER)
	gcc $(FLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re