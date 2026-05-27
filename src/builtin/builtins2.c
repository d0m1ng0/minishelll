/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anegorov <anegorov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/21 10:08:07 by anegorov          #+#    #+#             */
/*   Updated: 2026/05/27 16:33:48 by anegorov         ###   ########.fr       */
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
		return (-1);
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

static int	handle_export_arg(t_env **env, char *arg)
{
	t_env	*new_env;
	t_env	*old;

	if (!is_var_valid(arg))
	{
		print_error("export", arg, "not a valid identifier");
		return (1);
	}
	new_env = env_new(arg);
	if (!new_env)
		return (-1);
	old = find_env(*env, new_env->key);
	if (update_env_value(old, new_env))
		return (-1);
	if (!old)
		env_add_back(env, new_env);
	return (0);
}

int	builtin_export(t_env **env, char **ar)
{
	size_t	i;
	int		ret;
	int		status;

	i = 1;
	status = 0;
	if (!ar[1])
		return (print_export(*env));
	while (ar[i])
	{
		ret = handle_export_arg(env, ar[i]);
		if (ret == 1)
			status = 1;
		else if (ret == -1)
			return (-1);
		i++;
	}
	return (status);
}
