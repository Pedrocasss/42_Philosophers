# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: psoares- <psoares-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/07 19:04:12 by psoares-          #+#    #+#              #
#    Updated: 2023/11/10 18:50:20 by psoares-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = cc 

CFLAGS = -Wall -Wextra -Werror -pthread #-fsanitize=thread #-fsanitize=address -fsanitize=thread -g3## 

RM = rm -f

SRCS = free_all.c \
		init_all.c \
		main.c \
		print.c \
		routine.c \
		monitor.c \
		utils_philo.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	$(RM) $(OBJS)

fclean:
	$(RM) $(NAME) $(OBJS)

re: fclean $(NAME)

.PHONY: all clean fclean re