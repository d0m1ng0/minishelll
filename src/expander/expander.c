/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anegorov <anegorov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/21 13:13:53 by anegorov          #+#    #+#             */
/*   Updated: 2026/05/22 18:02:59 by anegorov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

static int	init_expand(t_expand *exp)
{
	exp->i = 0;
	exp->state = NO_QUOTE;
	exp->result = ft_strdup("");
	if (!exp->result)
		return (1);
	return (0);
}

static int	handle_quotes(char *str, t_expand *exp)
{
	if (str[exp->i] == '\'' && exp->state == NO_QUOTE)
	{
		exp->state = SINGLE_QUOTE;
		exp->i++;
		return (1);
	}
	if (str[exp->i] == '\'' && exp->state == SINGLE_QUOTE)
	{
		exp->state = NO_QUOTE;
		exp->i++;
		return (1);
	}
	if (str[exp->i] == '"' && exp->state == DOUBLE_QUOTE)
	{
		exp->state = NO_QUOTE;
		exp->i++;
		return (1);
	}
	if (str[exp->i] == '"' && exp->state == NO_QUOTE)
	{
		exp->state = DOUBLE_QUOTE;
		exp->i++;
		return (1);
	}
	return (0);
}

// if (is_start && (ft_isalpha(c) || c == '_'))
	// 	return (1);

int	is_var_char(char c)
{
	if ((ft_isalnum(c) || c == '_'))
		return (1);
	return (0);
}

static char	*extract_value(char *str, t_expand *exp, t_shell *shell)
{
	size_t	start;
	char	*key;
	char	*value;

	start = exp->i;
	while (str[exp->i] && is_var_char(str[exp->i]))
		exp->i++;
	key = ft_substr(str, start, exp->i - start);
	if (!key)
		return (NULL);
	value = get_env_value(shell->env, key);
	free(key);
	if (!value)
		return (ft_strdup(""));
	return (ft_strdup(value));
}

static int	append_str(t_expand *exp, char *str)
{
	char	*old;

	old = exp->result;
	exp->result = ft_strjoin(exp->result, str);
	free(old);
	if (!exp->result)
		return (1);
	return (0);
}

static int	append_char(t_expand *exp, char c)
{
	char	*old;
	char	word[2];

	word[0] = c;
	word[1] = '\0';
	old = exp->result;
	exp->result = ft_strjoin(exp->result, word);
	free(old);
	if (!exp->result)
		return (1);
	return (0);
}

static int	handle_dollar(char *str, t_expand *exp, t_shell *shell)
{
	char	*value;

	exp->i++;
	if (str[exp->i] == '?')
	{
		value = ft_itoa(shell->exit_status);
		if (!value)
			return (1);
		exp->i++;
	}
	else if (is_var_char(str[exp->i]))
		value = extract_value(str, exp, shell);
	else
		value = ft_strdup("$");
	if (!value)
		return (1);
	if (append_str(exp, value))
		return (free(value), 0);
	free(value);
	return (0);
}

static int	process_arg(char **arg, t_shell *shell)
{
	t_expand	exp;
	char		*old;

	if (init_expand(&exp))
		return (1);
	while ((*arg)[exp.i])
	{
		if (handle_quotes(*arg, &exp))
			continue ;
		if ((*arg)[exp.i] == '$'
			&& exp.state != SINGLE_QUOTE)
		{
			if (handle_dollar(*arg, &exp, shell))
				return (free(exp.result), 1);
			continue ;
		}
		if (append_char(&exp, (*arg)[exp.i]))
			return (1);
		exp.i++;
	}
	old = *arg;
	*arg = exp.result;
	free(old);
	return (0);
}

int	expand_var(t_cmd *cmd, t_shell *shell)
{
	size_t		i;

	while (cmd)
	{
		i = 0;
		while (cmd->argv[i])
		{
			if (process_arg(&cmd->argv[i], shell))
				return (1);
			i++;
		}
		cmd = cmd->next;
	}
	return (0);
}
