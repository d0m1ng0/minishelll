/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_operator.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anegorov <anegorov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/16 12:28:54 by anegorov          #+#    #+#             */
/*   Updated: 2026/05/17 18:17:37 by anegorov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/lexer.h"
#include "../../include/token_utils.h"

static int	handle_pipe(t_lexer *lexer)
{
	t_token	*new_token;

	new_token = ft_new_token(TOKEN_PIPE, "|");
	if (!new_token)
		return (1);
	add_token(&lexer->tokens, new_token);
	lexer->pos++;
	return (0);
}

static int	handle_input_redirection(t_lexer *lexer)
{
	t_token	*new_token;

	if (lexer->input[lexer->pos + 1] == '<')
	{
		new_token = ft_new_token(TOKEN_HEREDOC, "<<");
		lexer->pos += 2;
	}
	else
	{
		new_token = ft_new_token(TOKEN_REDIR_IN, "<");
		lexer->pos++;
	}
	if (!new_token)
		return (1);
	add_token(&lexer->tokens, new_token);
	return (0);
}

static int	handle_output_redirection(t_lexer *lexer)
{
	t_token	*new_token;

	if (lexer->input[lexer->pos + 1] == '>')
	{
		new_token = ft_new_token(TOKEN_APPEND, ">>");
		lexer->pos += 2;
	}
	else
	{
		new_token = ft_new_token(TOKEN_REDIR_OUT, ">");
		lexer->pos++;
	}
	if (!new_token)
		return (1);
	add_token(&lexer->tokens, new_token);
	return (0);
}

int	handle_operator(t_lexer *lexer)
{
	if (lexer->input[lexer->pos] == '|')
		return (handle_pipe(lexer));
	else if (lexer->input[lexer->pos] == '<')
		return (handle_input_redirection(lexer));
	else if (lexer->input[lexer->pos] == '>')
		return (handle_output_redirection(lexer));
	return (0);
}
