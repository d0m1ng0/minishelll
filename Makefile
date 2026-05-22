# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dverdini <dverdini@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/05/16 12:07:21 by dverdini          #+#    #+#              #
#    Updated: 2026/05/22 12:37:26 by dverdini         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

FT_PRINTF_DIR = ./ft_printf

FT_PRINTF = $(FT_PRINTF_DIR)/libftprintf.a

LIBFT_DIR = ./libft

LIBFT = $(LIBFT_DIR)/libft.a

# ----------------------- BONUS ------------------------------------------------
# ------------------------------------------------------------------------------

CC = cc

CFLAGS = -Wall -Wextra -Werror -lreadline -Iincludes -I$(LIBFT_DIR) -I$(FT_PRINTF_DIR)

RM = rm -f

# ------------------------------------------------------------------------------

SRCS = src/main.c \
	src/read_line.c 

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS) $(FT_PRINTF) $(LIBFT) 
	$(CC) $(CFLAGS) $(OBJS) $(FT_PRINTF) $(LIBFT) -o $(NAME)

$(FT_PRINTF):
	@make -C $(FT_PRINTF_DIR)

$(LIBFT):
	@make -C $(LIBFT_DIR)

%.o:%.c 
	$(CC) $(CFLAGS) -c $< -o  $@

clean:
	$(RM) $(OBJS)
	@make -C $(FT_PRINTF_DIR) clean
	@make -C $(LIBFT_DIR) clean

fclean: clean
	$(RM) $(NAME)
	@make -C $(FT_PRINTF_DIR) fclean
	@make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re

