/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anegorov <anegorov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/16 16:23:04 by anegorov          #+#    #+#             */
/*   Updated: 2026/05/17 19:24:20 by anegorov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "parser.h"

#include <stdio.h>
#include <stdlib.h>

#include "builtin.h"

t_cmd	*build_cmds(char *line);

// void execute_cmd(t_cmd *cmd)
// {
// 	getenv("PATH");
// }


void	execute_single_cmd(t_cmd *cmd)
{
	if (!cmd->argv || !cmd->argv[0])
		return ;
	if (is_builtin(cmd->argv[0]))
		run_builtin(cmd);
	// else
	// 	run_external(cmd);
}

void	executor(t_cmd *cmd)
{
	while (cmd)
	{
		execute_single_cmd(cmd);
		cmd = cmd->next;
	}
}

int	main(void)
{
	t_cmd	*cmd;
	t_cmd	*tmp;
	char	*line;
	size_t	i;

	while (1)
	{
		line = readline("minishell> ");
		if (!line)
			break ;
		cmd = build_cmds(line);
		if (!cmd)
			return (free(line), printf("memory error\n"), 1);
		tmp = cmd;
		while (tmp)
		{
			i = 0;
			while (tmp->argv && tmp->argv[i])
			{
				printf("ARGV[%zu]: %s file: %s output: %s\n", i,
					tmp->argv[i], tmp->infile, tmp->outfile);
				i++;
			}
			tmp = tmp->next;
		}
		// expend(*, $var);execute();free everything
		executor(cmd);
		free(line);
		free_cmds(cmd);
	}
	return (0);
}
