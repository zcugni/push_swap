# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zcugni <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/02/12 14:27:13 by zcugni            #+#    #+#              #
#    Updated: 2018/02/12 14:27:15 by zcugni           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME_1 = checker

NAME_2 = push_swap

SRCS_1 = checker.c lst_func.c op.c

SRCS_2 = push_swap.c lst_func.c op.c misc.c

OBJS_1 = $(SRCS_1:%.c=%.o)

OBJS_2 = $(SRCS_2:%.c=%.o)

L_PATH = libft/

LIB = ft

FLAGS = -Wall -Werror -Wextra

all: $(NAME_1) $(NAME_2)

$(NAME_1): lmake
	gcc $(FLAGS) -I$(L_PATH) -c $(SRCS_1)
	gcc $(FLAGS) -I$(L_PATH) -L$(L_PATH) -l$(LIB) -o $(NAME_1) $(OBJS_1)

$(NAME_2): lmake
	gcc $(FLAGS) -I$(L_PATH) -c $(SRCS_2)
	gcc $(FLAGS) -I$(L_PATH) -L$(L_PATH) -l$(LIB) -o $(NAME_2) $(OBJS_2)

lmake : 
	@$(MAKE) -C $(L_PATH)

clean:
	rm -f $(OBJS_1) $(OBJS_2)
	@$(MAKE) clean -C $(L_PATH)

fclean: clean
	rm -f $(NAME_1) $(NAME_2)
	@$(MAKE) fclean -C $(L_PATH)

re : fclean lmake all

.PHONY: clean fclean all re