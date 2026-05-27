/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anegorov <anegorov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/21 10:08:07 by anegorov          #+#    #+#             */
/*   Updated: 2026/05/27 14:15:41 by anegorov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtin.h"

static	t_env	**env_to_arr(t_env *env)
{
	size_t	i;
	size_t	size;
	t_env	**arr;

	size = env_size(env);
	arr = (t_env **)malloc(sizeof(t_env *) * (size + 1));
	if (!arr)
		return (NULL);
	i = 0;
	while (env)
	{
		arr[i++] = env;
		env = env->next;
	}
	arr[i] = NULL;
	return (arr);
}

static void	swap_env(t_env **a, t_env **b)
{
	t_env	*tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

static void	sort_env_arr(t_env **arr)
{
	size_t	i;
	size_t	j;
	size_t	len;
	int		cmp;

	i = 0;
	while (arr[i])
	{
		j = i + 1;
		while (arr[j])
		{
			len = ft_strlen(arr[i]->key);
			cmp = ft_strncmp(arr[i]->key, arr[j]->key, len + 1);
			if (cmp > 0)
				swap_env(&arr[i], &arr[j]);
			j++;
		}
		i++;
	}
}

int	print_export(t_env *env)
{
	t_env	**arr;
	size_t	i;

	arr = env_to_arr(env);
	if (!arr)
		return (1);
	sort_env_arr(arr);
	i = 0;
	while (arr[i])
	{
		if (arr[i]->exported)
		{
			if (arr[i]->value)
				printf("declare -x %s=\"%s\"\n", arr[i]->key, arr[i]->value);
			else
				printf("declare -x %s\n", arr[i]->key);
		}
		i++;
	}
	free(arr);
	return (0);
}

int	builtin_export(t_env **env, char **ar)
{
	size_t	i;
	t_env	*new_env;
	t_env	*old;

	i = 1;
	if (!ar[1])
		return (print_export(*env));
	while (ar[i])
	{
		if (!is_var_valid(ar[i]))
		{
			print_error("export", ar[i], "not a valid identifier");
			continue ;
		}
		new_env = env_new(ar[i]);
		if (!new_env)
			return (1);
		old = find_env(*env, new_env->key);
		if (update_env_value(old, new_env))
			return (1);
		else if (!old)
			env_add_back(env, new_env);
		i++;
	}
	return (0);
}
