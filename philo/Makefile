# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hali-mah <hali-mah@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/06 12:09:46 by hali-mah          #+#    #+#              #
#    Updated: 2025/04/04 11:18:00 by hali-mah         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread
SRCS = src/actions.c \
	  src/cleanup.c \
	  src/init_philosophers.c \
	  src/init_table.c \
	  src/main.c \
	  src/routine.c \
	  src/monitor.c \
	  src/simulation.c \
	  utilities/ft_atoi.c \
	  utilities/utils.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all