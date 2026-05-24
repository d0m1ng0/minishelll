/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dverdini <dverdini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/23 16:46:04 by dverdini          #+#    #+#             */
/*   Updated: 2026/05/24 13:43:50 by dverdini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "parser.h"

/* --------------------------------------------------------------------------*/
void	ms_executor(t_cmd *cmd, char **envp);
void	ms_execute_single_cmd(t_cmd *cmd, char **envp);

char	*ms_get_path_value(char **envp);
char	*ms_create_path_candidate(char *dir, char *cmd);
char	*ms_find_cmd_path(char *cmd, char **envp);
void	ms_run_external(t_cmd *cmd, char **envp);
/* --------------------------------------------------------------------------*/
#endif
