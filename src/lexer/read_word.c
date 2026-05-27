/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_word.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dverdini <dverdini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/23 13:10:25 by dverdini          #+#    #+#             */
/*   Updated: 2026/05/23 13:10:36 by dverdini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ms_read_word(char *line, int *i)
{
	int	start;
	char	*word;

	start = *i;
	while (line[*i] && !ms_is_space(line[*i])
			&& !ms_is_operator(line[*i]))
	{	
		(*i)++;
	}
	word = ft_substr(line, start, *i - start);
	return (word);
}
