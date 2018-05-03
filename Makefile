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

#va falloir que je change ca apres
SRCS_1 = checker.c lst_func.c op.c valid_input.c misc.c

SRCS_2 = push_swap.c lst_func.c op.c misc.c valid_input.c sort.c move.c

OBJS_1 = $(SRCS_1:%.c=objs/%.o)

OBJS_2 = $(SRCS_2:%.c=objs/%.o)

L_PATH = libft/

LIB = ft

FLAGS = -Wall -Werror -Wextra

objs/%.o : %.c
	@echo "compilation : " $*
	@gcc $(FLAGS) -c $^ -o $@ -I.

all: $(NAME_1) $(NAME_2)

$(NAME_1): lmake $(OBJS_1)
	@echo "compilation : " $(NAME_1)
	@gcc $(FLAGS) $(OBJS_1) -L$(L_PATH) -l$(LIB) -o $(NAME_1)

$(NAME_2): lmake $(OBJS_2)
	@echo "compilation : " $(NAME_2)
	@gcc $(FLAGS) $(OBJS_2) -L$(L_PATH) -l$(LIB) -o $(NAME_2) 

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