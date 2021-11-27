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
	srcs/ft_split.c \
	srcs/ft_substr.c \
	srcs/ft_memchr.c \
	srcs/ft_memmove.c \
	srcs/ft_memcpy.c \
	srcs/ft_echo.c \
	srcs/ft_pwd.c \
	srcs/ft_cd.c \
	srcs/ft_cd_nullify_preceding_pathname.c \
	srcs/ft_env.c \
	srcs/ft_export.c \
	srcs/ft_export_helpers.c \
	srcs/ft_export_helpers2.c \
	srcs/ft_unset.c \
	srcs/pipe.c \

OBJ = $(SRC:%.c=%.o)

FLAGS = -Wall -Wextra -Werror -I /Users/timur/.brew/opt/readline/include

READLINE = -lreadline -L /Users/timur/.brew/opt/readline/lib

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