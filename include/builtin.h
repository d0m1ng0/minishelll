/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anegorov <anegorov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/17 15:16:35 by anegorov          #+#    #+#             */
/*   Updated: 2026/06/09 10:58:52 by anegorov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "libft.h"
# include "parser.h"
# include "shell.h"
# include "env.h"
# include <errno.h>
# include <string.h>
# include <ft_printf.h>

typedef struct s_builtin
{
	char	*name;
	int		(*func)(t_cmd *cmd);
}	t_builtin;

int		is_builtin(char *cmd);
int		is_equal(char *a, char *b);
int		builtin_echo(char **argv);
int		builtin_pwd(t_shell *shell);
int		builtin_cd(char **argv, t_shell *shell);
int		builtin_env(t_env *env);
int		builtin_export(t_env **env, char **argv);
int		builtin_unset(t_env **env, char **argv);
int		builtin_exit(char **argv, t_shell *shell);
int		run_builtin(t_cmd *cmd, t_env **env, t_shell *shell);
void	print_error(char *cmd, char *arg, char *msg);
void	swap_env(t_env **a, t_env **b);

#endif