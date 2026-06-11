/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anegorov <anegorov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/22 18:18:28 by anegorov          #+#    #+#             */
/*   Updated: 2026/06/05 13:56:41 by anegorov         ###   ########.fr       */
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

void	remove_empty_args(char **argv)
{
	int	i;
	int	j;

	if (!argv)
		return ;
	i = 0;
	j = 0;
	while (argv[i])
	{
		if (argv[i][0] != '\0')
			argv[j++] = argv[i];
		else
			free(argv[i]);
		i++;
	}
	argv[j] = NULL;
}
