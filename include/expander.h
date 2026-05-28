/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anegorov <anegorov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/22 14:14:15 by anegorov          #+#    #+#             */
/*   Updated: 2026/05/28 10:48:42 by anegorov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "lexer.h"
# include "parser.h"
# include "env.h"
# include "shell.h"

typedef struct s_expand
{
	size_t	i;
	t_quote	state;
	char	*result;
}	t_expand;

int	expand_var(t_cmd *cmd, t_shell *shell);
int	init_expand(t_expand *exp);
int	handle_quotes(char *str, t_expand *exp);
int	append_str(t_expand *exp, char *str);
int	append_char(t_expand *exp, char c);

#endif