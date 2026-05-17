/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anegorov <anegorov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/16 11:24:42 by anegorov          #+#    #+#             */
/*   Updated: 2026/05/17 16:04:54 by anegorov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include <stdlib.h>
# include <stdio.h>
# include "token_utils.h"
# include "libft.h"
# include <readline/readline.h>
# include <readline/history.h>

typedef enum e_quote
{
	NO_QUOTE,
	SINGLE_QUOTE,
	DOUBLE_QUOTE
}	t_quote;

typedef struct s_lexer
{
	char	*input;
	size_t	pos;
	t_token	*tokens;
}	t_lexer;

int		ft_isspace(char c);
int		ft_isoperator(char c);
size_t	ft_strlen(const char *str);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
char	*ft_strdup(const char *str);
char	*ft_substr(const char *s, unsigned int start, size_t len);
int		handle_operator(t_lexer *lexer);
int		handle_word(t_lexer *lexer);
t_lexer	*lexer_init(char *input);
int		tokenize(t_lexer *lexer);
void	free_lexer(t_lexer *lexer);

#endif