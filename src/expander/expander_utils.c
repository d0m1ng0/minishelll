/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anegorov <anegorov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/22 18:18:28 by anegorov          #+#    #+#             */
/*   Updated: 2026/05/22 18:19:58 by anegorov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

int	init_expand(t_expand *exp)
{
	exp->i = 0;
	exp->state = NO_QUOTE;
	exp->result = ft_strdup("");
	if (!exp->result)
		return (1);
	return (0);
}

int	handle_quotes(char *str, t_expand *exp)
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

int	append_str(t_expand *exp, char *str)
{
	char	*old;

	old = exp->result;
	exp->result = ft_strjoin(exp->result, str);
	free(old);
	if (!exp->result)
		return (1);
	return (0);
}

int	append_char(t_expand *exp, char c)
{
	char	*old;
	char	word[2];

	word[0] = c;
	word[1] = '\0';
	old = exp->result;
	exp->result = ft_strjoin(exp->result, word);
	free(old);
	if (!exp->result)
		return (1);
	return (0);
}
