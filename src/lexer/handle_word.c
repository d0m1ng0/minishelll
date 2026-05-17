/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_word.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anegorov <anegorov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/16 12:48:10 by anegorov          #+#    #+#             */
/*   Updated: 2026/05/17 18:17:41 by anegorov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/lexer.h"

static void	handle_no_quote(char c, t_quote *quote_state)
{
	if (c == '\'')
		*quote_state = SINGLE_QUOTE;
	else if (c == '"')
		*quote_state = DOUBLE_QUOTE;
}

static void	handle_second_quote(char c, t_quote *quote_state)
{
	if (*quote_state == SINGLE_QUOTE && c == '\'')
		*quote_state = NO_QUOTE;
	else if (*quote_state == DOUBLE_QUOTE && c == '"')
		*quote_state = NO_QUOTE;
}

static void	scan_word(t_lexer *lexer)
{
	char	c;
	t_quote	quote_state;

	quote_state = NO_QUOTE;
	while (lexer->input[lexer->pos])
	{
		c = lexer->input[lexer->pos];
		if (quote_state == NO_QUOTE)
		{
			handle_no_quote(c, &quote_state);
			if (ft_isspace(c) || ft_isoperator(c))
				break ;
		}
		else
			handle_second_quote(c, &quote_state);
		lexer->pos++;
	}
}

static char	*extract_word(char *word, char *input, size_t start, size_t len)
{
	size_t	i;
	size_t	j;
	t_quote	quote_state;

	quote_state = NO_QUOTE;
	i = 0;
	j = 0;
	while (i < len)
	{
		if (quote_state == NO_QUOTE)
		{
			handle_no_quote(input[start + i], &quote_state);
			if (quote_state == NO_QUOTE)
				word[j++] = input[start + i];
		}
		else if ((quote_state == SINGLE_QUOTE && input[start + i] == '\'')
			|| (quote_state == DOUBLE_QUOTE && input[start + i] == '"'))
			quote_state = NO_QUOTE;
		else
			word[j++] = input[start + i];
		i++;
	}
	word[j] = '\0';
	return (word);
}

int	handle_word(t_lexer *lexer)
{
	size_t	start;
	t_token	*new_token;
	char	*word;

	start = lexer->pos;
	scan_word(lexer);
	word = malloc(sizeof(char) * (lexer->pos - start + 1));
	if (!word)
		return (1);
	extract_word(word, lexer->input, start, lexer->pos - start);
	new_token = ft_new_token(TOKEN_WORD, word);
	if (!new_token)
	{
		free(word);
		return (1);
	}
	free(word);
	add_token(&lexer->tokens, new_token);
	return (0);
}
