/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_to_envp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anegorov <anegorov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 11:20:53 by anegorov          #+#    #+#             */
/*   Updated: 2026/05/30 22:22:25 by anegorov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

t_env	*create_env_node(char *key, char *value)
{
	t_env	*node;

	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	node->key = ft_strdup(key);
	if (!node->key)
		return (free(node), NULL);
	if (value)
	{
		node->value = ft_strdup(value);
		if (!node->value)
			return (free(node->key), free(node), NULL);
	}
	else
		node->value = NULL;
	node->exported = 1;
	node->next = NULL;
	return (node);
}

int	set_env_value(t_env **env, char *key, char *value)
{
	t_env	*node;

	node = find_env(*env, key);
	if (node)
	{
		free(node->value);
		node->value = ft_strdup(value);
		if (value && !node->value)
			return (1);
	}
	else
	{
		node = create_env_node(key, value);
		if (!node)
			return (1);
		env_add_back(env, node);
	}
	return (0);
}

void	free_envp(char **envp)
{
	int	i;

	if (!envp)
		return ;
	i = 0;
	while (envp[i])
		free(envp[i++]);
	free(envp);
}

char	*env_join(char *key, char *value)
{
	char	*tmp;
	char	*res;

	if (!value || !key)
		return (NULL);
	tmp = ft_strjoin(key, "=");
	if (!tmp)
		return (NULL);
	res = ft_strjoin(tmp, value);
	free(tmp);
	return (res);
}

char	**env_to_envp(t_env *env)
{
	char	**envp;
	int		i;
	int		size;

	size = env_size(env);
	envp = malloc(sizeof(char *) * (size + 1));
	if (!envp)
		return (NULL);
	i = 0;
	while (env)
	{
		if (env->value)
			envp[i] = env_join(env->key, env->value);
		else
			envp[i] = ft_strdup(env->key);
		if (!envp[i])
		{
			free_envp(envp);
			return (NULL);
		}
		i++;
		env = env->next;
	}
	envp[i] = NULL;
	return (envp);
}
