/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anegorov <anegorov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/21 13:13:53 by anegorov          #+#    #+#             */
/*   Updated: 2026/05/22 15:13:32 by anegorov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

static int	init_expand(t_expand *exp)
{
	exp->i = 0;
	exp->state = NO_QUOTE;
	exp->result = ft_strdup("");
	if (!exp->result)
		return (1);
	return (0);
}

static int	handle_quotes(char *str, t_expand *exp)
{
	if (str[exp->i] == '\'' && exp->state == NO_QUOTE)
	{
		exp->state = SINGLE_QUOTE;
		exp->i++;
		return (1);
	}
	if (str[exp->i] == '\'' && exp->state == SINGLE_QUOTE)
	{
		exp->state = NO_QUOTE;
		exp->i++;
		return (1);
	}
	if (str[exp->i] == '"' && exp->state == DOUBLE_QUOTE)
	{
		exp->state = NO_QUOTE;
		exp->i++;
		return (1);
	}
	if (str[exp->i] == '"' && exp->state == NO_QUOTE)
	{
		exp->state = DOUBLE_QUOTE;
		exp->i++;
		return (1);
	}
	return (0);
}

char	*expand_var(t_cmd *cmd, t_shell *shell)
{
	t_expand	exp;
	size_t		i;

	i = 0;
	if (init_expand(&exp))
		return (NULL);
	while (cmd->argv[i])
	{
		exp.i = 0;
		exp.state = NO_QUOTE;
		while (cmd->argv[i][exp.i])
		{
			if (handle_quotes(cmd->argv[i], &exp))
				continue ;
			if (cmd->argv[i][exp.i] == '$' && exp.state != SINGLE_QUOTE)
			{
				if (handle_dollar(cmd->argv[i], &exp, shell))
					
				continue ;
			}
			exp.i++;
		}
		i++;
	}
	return (exp.result);
}
