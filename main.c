/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anegorov <anegorov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/16 16:23:04 by anegorov          #+#    #+#             */
/*   Updated: 2026/05/16 17:33:15 by anegorov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "parser.h"

int	main(int argc, char **argv)
{
	t_lexer	*lexer;
	t_cmd	*cmd;
	char	*line;

	(void)argc;
	(void)argv;
	while (1)
	{
		line = readline("minishell> ");
		if (!line)
			break ;
		lexer = lexer_init(line);
		tokenize(lexer);
		while (lexer->tokens)
		{
			printf("Token: Type=%d, Value=%s\n", lexer->tokens->type,
				lexer->tokens->value);
			lexer->tokens = lexer->tokens->next;
		}
		cmd = parser(lexer->tokens);
		if (!cmd)
			printf("memory error\n");
		// free everything ;execute();free everything
	}
	return (0);
}
