#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rbenjami <rbenjami@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2013/11/20 09:49:07 by rbenjami          #+#    #+#              #
#    Updated: 2013/11/20 11:31:21 by rbenjami         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

include		Makefile.sources

NAME		=	../lib3d.a

CFLAGS	=	-Wall -Wextra -Werror -O3 -g -pedantic

OBJ_LIB		=	$(SRC_LIB:.c=.o)

HEAD		=	lib3d.h

all:		$(NAME)

$(NAME):	$(OBJ_LIB)
	@ar -rc $(NAME) $(OBJ_LIB)
	@ranlib $(NAME)
	@echo ""
	@echo "\033[33m"Compilation of lib3d.a : "\033[32m"Succes"\033[0m"

$(OBJ_LIB):		$(HEAD)

%.o:		%.c
	@echo -n .
	@$(CC) $(CFLAGS) -c $< -o $@ $(INC)

clean:
	@echo "\033[31m"Objects of lib3d.a : deleted"\033[0m"
	@/bin/rm -f $(OBJ_LIB)

fclean:		clean
	@echo "\033[31m"lib3d.a : deleted"\033[0m"
	@/bin/rm -f $(NAME)

re:			fclean all

.PHONY:		all re fclean clean
