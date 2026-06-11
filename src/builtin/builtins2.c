/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anegorov <anegorov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/21 10:08:07 by anegorov          #+#    #+#             */
/*   Updated: 2026/06/11 19:27:32 by anegorov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtin.h"
#include <unistd.h>

// int	value_needs_dollar_quote(const char *v)
// {
// 	while (*v)
// 	{
// 		if (*v == '\n' || *v == '\r' || *v == '\t')
// 			return (1);
// 		v++;
// 	}
// 	return (0);
// }

static void	write_str(int fd, const char *s, size_t n)
{
	ssize_t	r;

	r = write(fd, s, n);
	(void)r;
}

// void	print_dollar_quoted(const char *v)
// {
// 	write_str(1, "$'", 2);
// 	while (*v)
// 	{
// 		if (*v == '\\')
// 			write_str(1, "\\\\", 2);
// 		else if (*v == '\'')
// 			write_str(1, "\\'", 2);
// 		else if (*v == '\n')
// 			write_str(1, "\\n", 2);
// 		else if (*v == '\r')
// 			write_str(1, "\\r", 2);
// 		else if (*v == '\t')
// 			write_str(1, "\\t", 2);
// 		else
// 			write_str(1, v, 1);
// 		v++;
// 	}
// 	write_str(1, "'", 1);
// }

void	print_double_quoted(const char *v)
{
	write_str(1, "\"", 1);
	while (*v)
	{
		if (*v == '\\')
			write_str(1, "\\\\", 2);
		else if (*v == '"')
			write_str(1, "\\\"", 2);
		else if (*v == '$')
			write_str(1, "\\$", 2);
		else
			write_str(1, v, 1);
		v++;
	}
	write_str(1, "\"", 1);
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
