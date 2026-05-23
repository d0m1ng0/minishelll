/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dverdini <dverdini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/17 10:30:51 by dverdini          #+#    #+#             */
/*   Updated: 2026/05/23 12:45:33 by dverdini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef  MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "ft_printf.h"
# include "libft.h"

# define TRUE 1
# define FALSE 0

typedef enum e_type
{
	TYPE_WORD,
	TYPE_PIPE,
	TYPE_REDIR_IN,
	TYPE_REDIR_OUT,
}	t_type;

typedef struct s_token
{
	t_type		type;
	char		*value;
	struct s_token	*next;
}	t_token;

char	*ms_read_line(void);


int	ms_is_space(char c);
int	ms_is_operator(char c);
char	*ms_read_word(char *line, int *i);
t_token	*ms_create_token(t_type type, char *value);
void	ms_add_token_back(t_token **tokens, t_token *new);

t_token	*ms_lexer(char *line);
void	ms_print_tokens(t_token *tokens);
void	ms_free_tokens(t_token *tokens);


void	ms_cleanup_line(char	*line);
void	ms_add_history(char *line);
void	ms_debug_print_line(char *line);
int	ms_handle_EOF(char *line);


#endif
