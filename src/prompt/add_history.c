/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_history.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dverdini <dverdini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/23 13:06:19 by dverdini          #+#    #+#             */
/*   Updated: 2026/05/23 13:06:40 by dverdini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_add_history(char *line)
{
	if (line == NULL)
		return ;
	if (line[0] == '\0')
		return ;
	add_history(line);
}


