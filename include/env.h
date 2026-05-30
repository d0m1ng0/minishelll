/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anegorov <anegorov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/21 09:28:18 by anegorov          #+#    #+#             */
/*   Updated: 2026/05/28 11:35:13 by anegorov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include "libft.h"
# include <stdio.h>

typedef struct s_env
{
	char			*key;
	char			*value;
	int				exported;
	struct s_env	*next;
}	t_env;

t_env	*env_new(char *envp);
void	env_add_back(t_env **env, t_env *new_env);
void	env_clear(t_env **env);
void	remove_env_var(t_env **env, char *key);
char	*get_env_value(t_env *env, char *key);
void	env_init(t_env **env, char **envp);
size_t	env_size(t_env	*env);
t_env	*find_env(t_env *env, char *key);
int		is_var_valid(char *s);
int		update_env_value(t_env *old, t_env *new_env);
char	**env_to_envp(t_env *env);
void	free_envp(char **envp);

#endif