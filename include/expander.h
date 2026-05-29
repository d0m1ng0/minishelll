/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anegorov <anegorov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/22 14:14:15 by anegorov          #+#    #+#             */
/*   Updated: 2026/05/29 18:35:11 by anegorov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "lexer.h"
# include "parser.h"
# include "env.h"
# include "shell.h"
# include <dirent.h>

typedef struct s_expand
{
	size_t	i;
	t_quote	state;
	char	*result;
}	t_expand;

typedef struct s_wc
{
	char	**matches;
	int		status;
}	t_wc;

int		expand_var(t_cmd *cmd, t_shell *shell);
int		init_expand(t_expand *exp);
int		handle_quotes(char c, t_expand *exp);
int		append_str(t_expand *exp, char *str);
int		append_char(t_expand *exp, char c);
int		expand_wildcards(t_cmd *cmd);
int		remove_quotes(t_cmd *cmd);
char	**insert_into_argv(char **argv, char **matches, int ind);
int		add_to_array(char ***arr, char *str);
int		ft_arrlen(char	**arr);
int		match(char *pattern, char *str);
int		has_wildcard(char *s);

#endif