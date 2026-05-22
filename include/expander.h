/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anegorov <anegorov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/22 14:14:15 by anegorov          #+#    #+#             */
/*   Updated: 2026/05/22 15:01:10 by anegorov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "lexer.h"
# include "parser.h"
# include "env.h"

typedef struct s_shell
{
	t_env	*env;
	int		exit_status;
}	t_shell;

typedef struct s_expand
{
	size_t	i;
	t_quote	state;
	char	*result;
}	t_expand;

char	*expand_var(t_cmd cmd, t_shell *shell);

#endif