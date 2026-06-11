# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anegorov <anegorov@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/05/16 12:07:21 by dverdini          #+#    #+#              #
#    Updated: 2026/06/11 19:17:46 by anegorov         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
NAME_BNS = minishell_bonus

CC = cc
# READLINE_INC = /nix/store/yz93n2svi7sqzrsjyvvfb35y4bbqr51f-readline-8.2p13-dev/include
# READLINE_LIB = /nix/store/1faijjgr6ai43v0mr3k0f8xajp5clh21-readline-8.2p13/lib
CFLAGS = -Wall -Wextra -Werror -MMD -MP
# -g3 -O1

SRC_DIR = src
OBJ_DIR = obj
INC_DIR = include

LIBFT_DIR = libft
LIB = $(LIBFT_DIR)/libft.a
FT_PRINTF_DIR = ft_printf
FT_PRINTF = $(FT_PRINTF_DIR)/libftprintf.a

SRC = \
lexer/lexer.c lexer/handle_operator.c lexer/handle_word.c lexer/lexer_utils.c lexer/token_utils.c \
parser/parser.c parser/cmd_building.c\
executor/executor.c \
executor/path.c \
executor/executor_ant.c executor/executor_single_ant.c executor/executor_child.c \
utils/free_split.c \
builtin/builtins.c builtin/builtins2.c builtin/builtins_utils.c builtin/exit.c builtin/cd.c builtin/export_utils.c\
env/env_init.c env/env_utils.c env/env_to_envp.c\
expander/expander.c expander/expander_utils.c expander/wildcard.c\
expander/remove_quotes.c expander/wildcard_utils.c expander/wildcard_utils2.c\
core/shell.c core/build_pipeline.c\
main.c\
signals/signals.c\
gnl/get_next_line.c gnl/get_next_line_utils.c

SRCS=$(addprefix $(SRC_DIR)/, $(SRC))

OBJ = $(SRC:src/%.c=$(OBJ_DIR)/%.o)
OBJS=$(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))
DEP = $(OBJS:.o=.d)


all: $(NAME)

bonus: $(NAME_BNS)

$(LIB):
	@make -C $(LIBFT_DIR)

$(FT_PRINTF):
	@make -C $(FT_PRINTF_DIR)

$(NAME): $(OBJS) $(LIB) $(FT_PRINTF)
	$(CC) $(OBJS) $(LIB) $(FT_PRINTF) -o $(NAME) -lreadline

$(NAME_BNS): $(OBJS) $(LIB) $(FT_PRINTF)
	$(CC) $(OBJS) $(LIB) $(FT_PRINTF) -o $(NAME) -lreadline

# $(CC) $(OBJS) $(LIB) $(FT_PRINTF) -o $(NAME) -L$(READLINE_LIB) -lreadline -Wl,-rpath,$(READLINE_LIB)

$(OBJ_DIR)/%.o: src/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -I$(INC_DIR) -I$(FT_PRINTF_DIR) -c $< -o $@

-include $(DEP)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all
