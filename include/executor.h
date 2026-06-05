/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anegorov <anegorov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/23 16:46:04 by dverdini          #+#    #+#             */
/*   Updated: 2026/06/05 16:55:52 by anegorov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "parser.h"
# include "env.h"
# include "shell.h"
# include "ft_printf.h"
# include "builtin.h"
# include "env.h"
# include <unistd.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <stdlib.h>
# include <readline/readline.h>
# include "expander.h"

/* --------------------------------------------------------------------------*/
void	ms_executor(t_cmd *cmd, t_env **env, t_shell *shell);
void	ms_execute_single_cmd(t_cmd *cmd, t_env **env, t_shell *shell);
void	ms_execute_pipe(t_cmd *cmd, char **envp, t_env **env, t_shell *shell);
char	*ms_get_path_value(char **envp);
char	*ms_create_path_candidate(char *dir, char *cmd);
char	*ms_find_cmd_path(char *cmd, char **envp);
void	ms_run_external(t_cmd *cmd, char **envp, t_shell *shell);
int	ms_run_heredoc(t_cmd *cmd);
/* --------------------------------------------------------------------------*/

void	executor(t_cmd *cmd, t_shell *shell);
void	executor_single(t_cmd *cmd, t_shell *shell, t_env **env);

#endif
