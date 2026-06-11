/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anegorov <anegorov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/16 16:23:04 by anegorov          #+#    #+#             */
/*   Updated: 2026/06/09 14:26:53 by anegorov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "parser.h"
#include <stdio.h>
#include <stdlib.h>
#include "builtin.h"
#include "env.h"
#include "expander.h"
#include "executor.h"
#include "shell.h"
#include "get_next_line.h"
#include "debug.h"
#include "signals.h"

// void print_cmd(t_cmd *cmd)
// {
//      size_t  i;
//      t_cmd   *tmp;

//      tmp = cmd;
//      while (tmp)
//      {
//              printf("----- CMD -----\n");
//              i = 0;
//              while (tmp->argv && tmp->argv[i])
//              {
//                      printf("ARGV[%zu]: %s\n", i, tmp->argv[i]);
//                      i++;
//              }
//              printf("INFILE: %s\n", tmp->infile ? tmp->infile : "NULL");
//              printf("OUTFILE: %s\n", tmp->outfile ? tmp->outfile : "NULL");
//              tmp = tmp->next;
//      }
// }

// void print_env(t_env *env)
// {
//      while (env)
//      {
//              if (env->exported == 1)
//                      printf("Key = %s Value = %s\n", env->key, env->value);
//              env = env->next;
//      }
// }

// int  main(int argc, char **argv, char **envp)
// {
//      t_cmd   *cmd;
//      char    *line;
//      t_shell shell;

//      (void)argc;
//      (void)argv;
//      if (init_shell(&shell, envp))
//              return (env_clear(&shell.env), perror("memory here: "), 1);
//      while (1)
//      {
//              line = readline("minishell> ");
//              if (!line)
//                      break ;
//              cmd = build_pipeline(line, &shell);
//              if (!cmd)
//                      return (free(line), env_clear(&shell.env),
							// perror("memory: "), 1);
//              ms_executor(cmd, &shell.env, &shell);
//              free(line);
//              free_cmds(cmd);
//      }
//      env_clear(&shell.env);
//      return (0);
// }
/* --- ANTONINA - EXECUTOR ----------------------------------------------*/
// int  execute_single_cmd(t_cmd *cmd, t_env **env, t_shell *shell)
// {
//      if (!cmd->argv || !cmd->argv[0])
//              return (0);
//      if (is_builtin(cmd->argv[0]))
//              return (run_builtin(cmd, env, shell));
//      return (0);
// }
// else
	//      run_external(cmd);

/*int   executor(t_cmd *cmd, t_env **env, t_shell *shell)
{
	int     status;

	while (cmd)
	{
		status = execute_single_cmd(cmd, env, shell);
		if (status == -1)
		{
			perror("minishell");
			exit(1);
		}
		shell->exit_status = status;
		cmd = cmd->next;
		if (shell->should_exit)
			exit(shell->exit_status);
	}
	return (0);
}
*/
/* --- ANTONINA - GNL ---------------------------------------------------*/

char	*get_line(void)
{
	char	*line;

	line = readline("minishell> ");
	if (!line)
		return (NULL);
	return (line);
}

static int	find_or_op(const char *line)
{
	int	i;
	int	in_single;
	int	in_double;

	i = 0;
	in_single = 0;
	in_double = 0;
	while (line[i])
	{
		if (line[i] == '\'' && !in_double)
			in_single = !in_single;
		else if (line[i] == '"' && !in_single)
			in_double = !in_double;
		else if (!in_single && !in_double
			&& line[i] == '|' && line[i + 1] == '|')
			return (i);
		i++;
	}
	return (-1);
}

static void	run_or_chain(char *line, t_shell *shell)
{
	int		or_pos;
	char	*segment;
	t_cmd	*cmd;

	while (line && *line)
	{
		or_pos = find_or_op(line);
		if (or_pos >= 0)
			segment = ft_substr(line, 0, or_pos);
		else
			segment = ft_strdup(line);
		if (segment && *segment)
		{
			cmd = build_pipeline(segment, shell);
			if (cmd)
			{
				executor(cmd, shell);
				free_cmds(cmd);
			}
		}
		free(segment);
		if (or_pos < 0 || shell->exit_status == 0)
			break ;
		line = line + or_pos + 2;
	}
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	t_shell	shell;

	(void)argc;
	(void)argv;
	if (init_shell(&shell, envp))
		return (env_clear(&shell.env), perror("memory: "), 1);
	ms_signals_setup();
	while (1)
	{
		line = get_line();
		if (!line)
			break ;
		if (line[0] == '\0')
		{
			free(line);
			continue ;
		}
		run_or_chain(line, &shell);
		free(line);
		if (shell.should_exit)
			break ;
	}
	return (env_clear(&shell.env), shell.exit_status);
}
