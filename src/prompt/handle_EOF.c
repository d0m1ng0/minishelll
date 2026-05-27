/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_EOF.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dverdini <dverdini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/23 13:07:10 by dverdini          #+#    #+#             */
/*   Updated: 2026/05/23 13:07:22 by dverdini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_handle_EOF(char *line)
{
	if (line == NULL)// receive ctrl-D
	{
		ft_printf("exit\n");
		return (1);
	}
	return (0);
}
