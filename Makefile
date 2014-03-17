# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rbenjami <rbenjami@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/02/26 13:13:47 by rbenjami          #+#    #+#              #
#    Updated: 2014/03/07 17:32:17 by rbenjami         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

include		libft/Makefile.sources
include		lib3d/Makefile.sources

export	CFLAGS	=	-Wall -Wextra -Werror -g

export	CC		=	cc

export	INC		=	-I $(PWD)/libft -I $(PWD)/lib3d

NAME		=	rt

INC			+=	-I includes -I/usr/X11R6/include

HEAD		=	includes/rt.h

SRC_DIR		=	srcs/

FILES		=	$(NAME).c	\
				parse.c		\
				error.c		\
				verify.c	\
				render.c	\
				hook.c		\
				color.c		\
				camera.c	\
				inter.c		\
				utils.c

SRC			=	$(addprefix $(SRC_DIR)/, $(FILES))

OBJ			=	$(SRC:.c=.o)

LIB			=	-L./ -L/usr/X11/lib -lft -l3d -lmlx -lXext -lX11

OBJ_LIBFT		=	$(libft/SRC_LIB:.c=.o)

HEAD_LIBFT	=	libft/libft.h libft/get_next_line.h libft/define_type.h

OBJ_LIB3D		=	$(lib3d/SRC_LIB:.c=.o)

HEAD_LIB3D	=	lib3d/lib3d.h

all:			libft.a $(NAME)

libft.a:		libft/$(OBJ_LIBFT) $(HEAD_LIBFT)
	@make -C libft

lib3d.a:		lib3d/$(OBJ_LIB3D) $(HEAD_LIB3D)
	@make -C lib3d

$(NAME):		$(OBJ)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIB)
	@echo ""
	@echo "\033[33m"compilation of $(NAME) : "\033[32m"Success"\033[0m"

$(OBJ):			$(HEAD) libft.a lib3d.a

%.o:			%.c $(HEAD)
	@echo -n .
	@$(CC) $(CFLAGS) -c $< -o $@ $(INC)

clean:
	@/bin/rm -f $(OBJ)
	@echo "\033[31m"Objects of $(NAME) : deleted"\033[0m"

fclean:			clean
	@/bin/rm -f $(NAME)
	@echo "\033[31m"$(NAME) : deleted"\033[0m"
	@make fclean -C libft
	@make fclean -C lib3d
re:				fclean all

.PHONY:			all clean fclean re

