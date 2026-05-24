/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dverdini <dverdini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/24 13:50:27 by dverdini          #+#    #+#             */
/*   Updated: 2026/05/24 13:52:00 by dverdini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	free_split(char **string)
{
	int	i;

	if (!string)
		return ;
	i = 0;
	while (string[i])
		free(string[i++]);
	free(string);
}
