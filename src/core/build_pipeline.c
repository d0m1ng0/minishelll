/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_pipeline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anegorov <anegorov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 15:24:46 by anegorov          #+#    #+#             */
/*   Updated: 2026/05/30 22:37:07 by anegorov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "parser.h"
#include "shell.h"
#include "expander.h"

static int	expand_cmd(t_cmd *cmd, t_shell *shell)
{
	if (expand_var(cmd, shell))
		return (1);
	if (expand_wildcards(cmd))
		return (1);
	return (0);
}

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
		shell->exit_status = 2;
		free_lexer(lexer);
		return (NULL);
	}
	cmd = parser(lexer->tokens);
	free_lexer(lexer);
	if (!cmd)
	{
		shell->exit_status = 2;
		return (NULL);
	}
	if (expand_cmd(cmd, shell))
		return (free_cmds(cmd), NULL);
	return (cmd);
}

	// if (remove_quotes(cmd))
	//      return (free_cmds(cmd), NULL);