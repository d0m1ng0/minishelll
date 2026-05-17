# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anegorov <anegorov@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/05/16 12:07:21 by dverdini          #+#    #+#              #
#    Updated: 2026/05/17 19:36:06 by anegorov         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror -MMD -MP

SRC_DIR = src
OBJ_DIR = obj
INC_DIR = include

LIB = libft.a

SRC = \
lexer/lexer.c lexer/handle_operator.c lexer/handle_word.c lexer/lexer_utils.c lexer/token_utils.c \
parser/parser.c parser/cmd_building.c\
builtin/builtin.c builtin/echo.c\
main.c build_cmds.c

SRCS=$(addprefix $(SRC_DIR)/, $(SRC))

OBJ = $(SRC:src/%.c=$(OBJ_DIR)/%.o)
OBJS=$(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))
DEP = $(OBJS:.o=.d)


all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(LIB) -o $(NAME) -lreadline

$(OBJ_DIR)/%.o: src/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@

-include $(DEP)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all