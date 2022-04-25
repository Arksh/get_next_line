# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cagonzal <cagonzal@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/11 10:48:11 by cagonzal          #+#    #+#              #
#    Updated: 2022/04/25 12:34:43 by cagonzal         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#	file's name
NAME = get_next_line.a
NAMEB = get_next_line_bonus.a

#	files
SRCS = get_next_line.c get_next_line_utils.c
SRCB = get_next_line_bonus.c get_next_line_utils_bonus.c
OBJS = ${SRCS:%.c=%.o}
OBJB = ${SRCB:%.c=%.o}
MAIN = main.c

#	flags
CFLAGS = -Wall -Werror -Wextra

#	options to create the library
AR = ar -rc

#	options to force the remove
RM = rm -f

#	compilation
CC = gcc

.c.o:
		${CC} ${CFLAGS} -g -c $< -o ${<:.c=.o}

all:	${NAME}

#	execute make
$(NAME): ${OBJS}
		${AR} ${NAME} ${OBJS}

#	execute make bonus
bonus: $(OBJB)
		$(AR) $(NAME) $(OBJB)

clean:
			${RM} *.o

fclean:		clean
			${RM} ${NAME}

re:		fclean $(NAME)

m:
	$(CC) $(CFLAGS) -D BUFFER_SIZE=42 $(SRCS) $(MAIN) \
		&& ./a.out lotr.txt

b:
	$(CC) $(CFLAGS) -D BUFFER_SIZE=10 $(SRCB) $(MAIN) \
		&& ./a.out lotr.txt other.txt

.PHONY:		all bonus clean fclean re