# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vlevko <vlevko@student.unit.ua>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/09 14:26:53 by popanase          #+#    #+#              #
#    Updated: 2018/09/02 12:19:22 by vlevko           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = corewar

SRC = main.c \
    check_args.c \
    start_fight.c \
    prinnt_func.c \
    fight_visual_1.c \
    fight_visual_2.c \
    check_isend.c \
    bit_handler.c \
    champ_handler.c \
    car_handler.c \
    ncurs.c \
    op.c \
    opcode_1_5.c \
    opcode_11_15.c \
    opcode_6_10.c \
    opcode_handler.c

OBJ = $(SRC:.c=.o)

# SDL = -L./SDL2/build/.libs/ -lSDL2
SDL = -F /Library/Frameworks -framework SDL2

all: $(NAME)

$(NAME): $(OBJ)
	make -C libft
	@#make -C ft_printf
	@#gcc -Wall -Wextra -Werror $^ -lncurses -L./libft -lft -L./ft_printf -lftprintf -o $@
	gcc -Wall -Wextra -Werror $^ $(SDL) -lpthread -lncurses -L./libft -lft -o $@
	
%.o: %.c
	gcc -Wall -Wextra -Werror -c $<

clean: 
	make clean -C libft
	@#make clean -C ft_printf
	rm -f $(OBJ)

fclean: clean 
	make fclean -C libft
	@#make fclean -C ft_printf
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
