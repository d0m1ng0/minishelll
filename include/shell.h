/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anegorov <anegorov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 14:58:25 by anegorov          #+#    #+#             */
/*   Updated: 2026/05/28 10:46:55 by anegorov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

# include "env.h"
# include "parser.h"

typedef struct s_shell
{
	t_env	*env;
	int		exit_status;
	int		should_exit;
}	t_shell;

int		init_shell(t_shell *shell, char **envp);
t_cmd	*build_pipeline(char *line, t_shell *shell);

#endif