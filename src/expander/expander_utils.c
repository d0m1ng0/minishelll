/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anegorov <anegorov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/22 18:18:28 by anegorov          #+#    #+#             */
/*   Updated: 2026/06/03 13:33:54 by anegorov         ###   ########.fr       */
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

void	ft_strswap(char **a, char **b)
{
	char	*tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}
