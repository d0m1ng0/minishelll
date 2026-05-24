/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anegorov <anegorov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/16 16:23:04 by anegorov          #+#    #+#             */
/*   Updated: 2026/05/24 12:18:15 by dverdini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "parser.h"

#include <stdio.h>
#include <stdlib.h>

#include "builtin.h"

#include "debug.h"
#include "executor.h"

t_cmd	*build_cmds(char *line);

// void execute_cmd(t_cmd *cmd)
// {
// 	getenv("PATH");
// }

/* COMMENTED SINCE I AM CREATING EXECUTOR
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
*/
void	print_cmd(t_cmd *cmd)
{
	size_t	i;
	t_cmd	*tmp;

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
}

int	main(int argc, char **argv, char **envp)
{
	t_cmd	*cmd;
	char	*line;

	(void)argc;
	(void)argv;
	//(void)envp;
	while (1)
	{
		line = readline("minishell> ");
		if (!line)
			break ;
		cmd = build_cmds(line);
		if (!cmd)
			return (free(line), printf("memory error\n"), 1);
		//print_cmd(cmd);
		print_cmds(cmd);
		// expend(*, $var);execute();free everything
		ms_executor(cmd, envp);
		free(line);
		free_cmds(cmd);
	}
	return (0);
}
