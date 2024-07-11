# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: leo <leo@student.42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/25 15:10:57 by lglauch           #+#    #+#              #
#    Updated: 2024/04/18 11:49:26 by leo              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CFLAGS	:= -Wextra -Wall -Werror
SRCS	:= src/main.c src/helper.c src/threads.c src/philo_utils.c src/clear.c
OBJS	:= ${SRCS:src/%.c=src/%.o}

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

src/%.o: src/%.c
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm -rf src/*.o

fclean: clean
	rm -rf $(NAME)

re: clean all
