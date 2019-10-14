# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vneelix <vneelix@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/23 22:34:46 by vneelix           #+#    #+#              #
#    Updated: 2019/10/04 20:40:03 by vneelix          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = general.c input.c fill.c bits_shifts.c output.c

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
