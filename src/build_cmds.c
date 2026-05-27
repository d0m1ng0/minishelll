/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_cmds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anegorov <anegorov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/16 18:50:40 by anegorov          #+#    #+#             */
/*   Updated: 2026/05/27 13:48:34 by anegorov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "parser.h"

void	print_tokens(t_token *tokens)
{
	while (tokens)
	{
		printf("Token: Type=%d, Value=%s\n", tokens->type, tokens->value);
		tokens = tokens->next;
	}
}

t_cmd	*build_cmds(char *line)
{
	t_lexer	*lexer;
	t_cmd	*cmd;
	int		tokenize_result;

	lexer = lexer_init(line);
	if (!lexer)
		return (NULL);
	tokenize_result = tokenize(lexer);
	if (tokenize_result)
	{
		free_lexer(lexer);
		return (NULL);
	}
	cmd = parser(lexer->tokens);
	free_lexer(lexer);
	if (!cmd)
	{
		return (NULL);
	}
	return (cmd);
}
	//--- print tokes to debug ---
	//print_tokens(lexer->tokens);
	//----------------------------
