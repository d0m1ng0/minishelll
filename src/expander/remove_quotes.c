/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anegorov <anegorov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 17:42:25 by anegorov          #+#    #+#             */
/*   Updated: 2026/05/29 18:35:52 by anegorov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

int	handle_quotes(char c, t_expand *exp)
{
	if (c == '\'' && exp->state == NO_QUOTE)
	{
		exp->state = SINGLE_QUOTE;
		return (1);
	}
	if (c == '\'' && exp->state == SINGLE_QUOTE)
	{
		exp->state = NO_QUOTE;
		return (1);
	}
	if (c == '"' && exp->state == DOUBLE_QUOTE)
	{
		exp->state = NO_QUOTE;
		return (1);
	}
	if (c == '"' && exp->state == NO_QUOTE)
	{
		exp->state = DOUBLE_QUOTE;
		return (1);
	}
	return (0);
}

static int	process_arg(char **arg)
{
	t_expand	exp;
	char		*old;

	if (init_expand(&exp))
		return (1);
	while ((*arg)[exp.i])
	{
		if (handle_quotes((*arg)[exp.i], &exp))
		{
			exp.i++;
			continue ;
		}
		if (append_char(&exp, (*arg)[exp.i]))
			return (1);
		exp.i++;
	}
	old = *arg;
	*arg = exp.result;
	free(old);
	return (0);
}

int	remove_quotes(t_cmd *cmd)
{
	size_t		i;

	while (cmd)
	{
		i = 0;
		while (cmd->argv && cmd->argv[i])
		{
			if (process_arg(&cmd->argv[i]))
				return (1);
			i++;
		}
		cmd = cmd->next;
	}
	return (0);
}
