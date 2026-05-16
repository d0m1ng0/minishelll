/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_cmds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anegorov <anegorov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/16 18:50:40 by anegorov          #+#    #+#             */
/*   Updated: 2026/05/16 18:52:44 by anegorov         ###   ########.fr       */
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

	lexer = lexer_init(line);
	tokenize(lexer);
	// print_tokens(lexer->tokens);
	cmd = parser(lexer->tokens);
	return (cmd);
}