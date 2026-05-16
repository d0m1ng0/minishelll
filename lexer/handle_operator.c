/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_operator.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anegorov <anegorov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/16 12:28:54 by anegorov          #+#    #+#             */
/*   Updated: 2026/05/16 16:35:51 by anegorov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lexer.h"
#include "../include/token_utils.h"

static void	handle_pipe(t_lexer *lexer)
{
	t_token	*new_token;

	new_token = ft_new_token(TOKEN_PIPE, "|");
	//if (!new_token)
		//destroy_all_exit(lexer);
	add_token(&lexer->tokens, new_token);
	lexer->pos++;
}

static void	handle_input_redirection(t_lexer *lexer)
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
	add_token(&lexer->tokens, new_token);
	//if (!new_token)
		//destroy_all_exit(lexer);
}

static void	handle_output_redirection(t_lexer *lexer)
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
	add_token(&lexer->tokens, new_token);
	//if (!new_token)
		//destroy_all_exit(lexer);
}

void	handle_operator(t_lexer *lexer)
{
	if (lexer->input[lexer->pos] == '|')
		handle_pipe(lexer);
	else if (lexer->input[lexer->pos] == '<')
		handle_input_redirection(lexer);
	else if (lexer->input[lexer->pos] == '>')
		handle_output_redirection(lexer);
}
