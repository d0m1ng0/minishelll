/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anegorov <anegorov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/21 10:08:07 by anegorov          #+#    #+#             */
/*   Updated: 2026/06/11 19:35:34 by anegorov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtin.h"

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
			if (ft_strlen(arr[j]->key) > len)
				len = ft_strlen(arr[j]->key);
			cmp = ft_strncmp(arr[i]->key, arr[j]->key, len + 1);
			if (cmp > 0)
				swap_env(&arr[i], &arr[j]);
			j++;
		}
		i++;
	}
}

t_env	**env_to_arr(t_env *env)
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

// static void	print_export_entry(t_env *e)
// {
// 	ft_putstr_fd("declare -x ", 1);
// 	ft_putstr_fd(e->key, 1);
// 	if (e->value)
// 	{
// 		ft_putstr_fd("=", 1);
// 		if (value_needs_dollar_quote(e->value))
// 			print_dollar_quoted(e->value);
// 		else
// 			print_double_quoted(e->value);
// 	}
// 	ft_putstr_fd("\n", 1);
// }

static void	print_export_entry(t_env *e)
{
	ft_putstr_fd("declare -x ", 1);
	ft_putstr_fd(e->key, 1);
	if (e->value)
	{
		ft_putstr_fd("=", 1);
	}
	ft_putstr_fd("\n", 1);
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
			print_export_entry(arr[i]);
		i++;
	}
	free(arr);
	return (0);
}

int	handle_export_arg(t_env **env, char *arg)
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
	new_env->exported = 1;
	old = find_env(*env, new_env->key);
	if (update_env_value(old, new_env))
		return (-1);
	if (!old)
		env_add_back(env, new_env);
	return (0);
}
