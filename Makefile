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
	srcs/ft_check_heredoc.c \
	srcs/ft_check_heredoc_helpers.c \
	srcs/redirect_input.c \
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
	srcs/ft_cd_helpers.c \
	srcs/ft_cd_helpers2.c \
	srcs/ft_env.c \
	srcs/ft_export.c \
	srcs/ft_export_helpers.c \
	srcs/ft_export_helpers2.c \
	srcs/ft_unset.c \
	srcs/ft_exit.c \
	srcs/ft_exit_helpers.c \
	srcs/ft_isdigit.c \
	srcs/pipe.c \
	srcs/bin.c \

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