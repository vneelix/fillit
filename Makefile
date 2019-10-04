# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vneelix <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/23 22:34:46 by vneelix           #+#    #+#              #
#    Updated: 2019/09/23 23:02:29 by vneelix          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = general.c input.c lstfunc.c

OBJS = $(SRCS:.c=.o)

INCLS = fillit.h

CFLAGS = -Wall -Wextra -Werror

NAME = fillit

.PHONY: all clean fclean re

%.o: %.c $(INCLS)
	gcc $(CFLAGS) -c $<

$(NAME): $(OBJS)
	gcc $(CFLAGS) $(OBJS) -o $(NAME)

all: $(NAME)

clean:
	rm -f $(OBJS)
fclean: clean
	rm -f $(NAME)

re: fclean all
