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

# define BUILTIN_OK 0
# define BUILTIN_ERR 1
# define BUILTIN_FATAL -1

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
int		print_export(t_env *env);
int		handle_export_arg(t_env **env, char *arg);
void	print_double_quoted(const char *v);
void	print_dollar_quoted(const char *v);
int		value_needs_dollar_quote(const char *v);

#endif