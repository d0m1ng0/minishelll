# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anegorov <anegorov@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/05/16 12:07:21 by dverdini          #+#    #+#              #
#    Updated: 2026/05/30 22:19:45 by anegorov         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror -MMD -MP -g3 -O0

SRC_DIR = src
OBJ_DIR = obj
INC_DIR = include

LIB = libft.a
FT_PRINTF_DIR = ft_printf
FT_PRINTF = $(FT_PRINTF_DIR)/libftprintf.a

SRC = \
lexer/lexer.c lexer/handle_operator.c lexer/handle_word.c lexer/lexer_utils.c lexer/token_utils.c \
parser/parser.c parser/cmd_building.c\
executor/executor.c \
executor/path.c \
utils/free_split.c \
builtin/builtins.c builtin/builtins2.c builtin/builtins_utils.c builtin/exit.c\
env/env_init.c env/env_utils.c env/env_to_envp.c\
expander/expander.c expander/expander_utils.c expander/wildcard.c\
expander/remove_quotes.c expander/wildcard_utils.c expander/wildcard_utils2.c\
core/shell.c core/build_pipeline.c\
main.c \
gnl/get_next_line.c gnl/get_next_line_utils.c\

SRCS=$(addprefix $(SRC_DIR)/, $(SRC))

OBJ = $(SRC:src/%.c=$(OBJ_DIR)/%.o)
OBJS=$(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))
DEP = $(OBJS:.o=.d)


all: $(NAME)

$(FT_PRINTF):
	@make -C $(FT_PRINTF_DIR)

$(NAME): $(OBJS) $(LIB) $(FT_PRINTF)
	$(CC) $(OBJS) $(LIB) $(FT_PRINTF) -o $(NAME) -lreadline


$(OBJ_DIR)/%.o: src/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -I$(INC_DIR)  -I$(FT_PRINTF_DIR) -c $< -o $@

-include $(DEP)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all
