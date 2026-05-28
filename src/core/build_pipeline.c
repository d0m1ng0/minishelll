/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_pipeline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anegorov <anegorov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 15:24:46 by anegorov          #+#    #+#             */
/*   Updated: 2026/05/28 10:17:04 by anegorov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "parser.h"
#include "shell.h"
#include "expander.h"

t_cmd	*build_pipeline(char *line, t_shell *shell)
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
		return (NULL);
	if (expand_var(cmd, shell))
	{
		return (free_cmds(cmd), NULL);
	}
	return (cmd);
}
