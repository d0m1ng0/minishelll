/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anegorov <anegorov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/16 16:23:04 by anegorov          #+#    #+#             */
/*   Updated: 2026/05/16 18:41:51 by anegorov         ###   ########.fr       */
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

int	main(void)
{
	t_lexer	*lexer;
	t_cmd	*cmd;
	char	*line;
	size_t	i;
	

	while (1)
	{
		line = readline("minishell> ");
		if (!line)
			break ;
		lexer = lexer_init(line);
		tokenize(lexer);
		print_tokens(lexer->tokens);
		cmd = parser(lexer->tokens);
		if (!cmd)
			printf("memory error\n");// free everything ;execute();free everything
		while (cmd)
		{
			i = 0;
			while (cmd->argv && cmd->argv[i])
			{
				printf("ARGV[%zu]: %s\n", i, cmd->argv[i]);
				i++;
			}
			cmd = cmd->next;
		}
		// free everything ;execute();free everything
	}
	return (0);
}
