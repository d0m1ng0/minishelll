/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anegorov <anegorov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/21 09:29:20 by anegorov          #+#    #+#             */
/*   Updated: 2026/05/28 12:56:30 by anegorov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

void	env_clear(t_env **env)
{
	t_env	*tmp;

	while (*env)
	{
		tmp = (*env)->next;
		if ((*env)->key)
			free((*env)->key);
		if ((*env)->value)
			free((*env)->value);
		free(*env);
		*env = tmp;
	}
	*env = NULL;
}

int	is_var_valid(char *s)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != '=')
	{
		if (i == 0 && !(ft_isalpha(s[i]) || s[i] == '_'))
			return (0);
		if (i && !(ft_isalnum(s[i]) || s[i] == '_'))
			return (0);
		i++;
	}
	return (1);
}

t_env	*env_new(char *envp)
{
	t_env	*new_env;
	char	*key;
	char	*value;
	size_t	i;

	new_env = malloc(sizeof(t_env));
	value = NULL;
	if (!new_env)
		return (NULL);
	i = 0;
	while (envp[i] && envp[i] != '=')
		i++;
	key = ft_substr(envp, 0, i);
	if (!key)
		return (free(new_env), NULL);
	if (envp[i])
	{
		value = ft_substr(envp, i + 1, ft_strlen(envp) - i - 1);
		if (!value)
			return (free(key), free(new_env), NULL);
	}
	new_env->value = value;
	new_env->key = key;
	new_env->next = NULL;
	return (new_env);
}

void	env_init(t_env **env, char **envp)
{
	t_env	*new_env;
	size_t	i;

	i = 0;
	*env = NULL;
	while (envp && envp[i])
	{
		new_env = env_new(envp[i]);
		if (!new_env)
			return (env_clear(env));
		new_env->exported = 1;
		env_add_back(env, new_env);
		i++;
	}
}

int	update_env_value(t_env *old, t_env *new_env)
{
	if (old && new_env->value)
	{
		free(old->value);
		old->value = ft_strdup(new_env->value);
		if (!old->value)
			return (1);
		env_clear(&new_env);
	}
	return (0);
}
