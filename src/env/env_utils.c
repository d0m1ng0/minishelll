/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anegorov <anegorov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/21 11:11:23 by anegorov          #+#    #+#             */
/*   Updated: 2026/05/21 12:50:40 by anegorov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

void	remove_env_var(t_env **env, char *key)
{
	t_env	*curr;
	t_env	*prev;

	curr = *env;
	prev = NULL;
	while (curr)
	{
		if (ft_strncmp(curr->key, key, ft_strlen(key)) == 0)
		{
			if (!prev)
				*env = curr->next;
			else
				prev->next = curr->next;
			if (curr->key)
				free(curr->key);
			if (curr->value)
				free(curr->value);
			free(curr);
			return ;
		}
		prev = curr;
		curr = curr->next;
	}
}

size_t	env_size(t_env	*env)
{
	size_t	i;

	i = 0;
	while (env)
	{
		env = env->next;
		i++;
	}
	return (i);
}
