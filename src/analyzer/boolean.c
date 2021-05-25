/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   boolean.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 19:05:24 by ciglesia          #+#    #+#             */
/*   Updated: 2021/05/25 19:09:10 by ciglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

/*
** op: | < > >>
** param: 2 non-op (spc: "" '' $)
*/

t_uchar	is_op(char *str)
{
	if (str && str[0])
	{
		if (str[0] == '<')
			return (1);
		if (str[0] == '>' && str[1] && str[1] == '>')
			return (3);
		if (str[0] == '>')
			return (2);
		if (str[0] == '|')
			return (4);
	}
	return (0);
}

int	end_of_token(char *str, int i, char quote)
{
	if (str[i] && (quote || (!ft_cspecial(&str[i]) && !is_op(&str[i])
				&& (str[i] != '$' || str[i + 1] == '$' || !str[i + 1]))))
		return (1);
	return (0);
}

int	is_bin(t_ast *node)
{
	char	*str;

	if (is_builtin(node->bin))
		node->type = 1;
	else
	{
		str = sh_which(node->bin, g_sh->ev);
		if (str)
		{
			node->type = 2;
			free (node->bin);
			node->bin = str;
		}
		else
			return (0);
	}
	return (1);
}

int	is_pipe(t_ast *node)
{
	if (!node->right || !node->left || node->right->op == 4)
	{
		ft_puterror(BOLD"minishell: syntax error inconsistent pipe\n", NULL);
		return (0);
	}
	if (node->right && node->right->bin && !is_bin(node->right))
	{
		ft_puterror(BOLD"minishell: semantic error after pipe:", NULL);
		if (node->left && node->left->bin)
		{
			ft_putstr_fd(" "BLUE, 2);
			ft_putstr_fd(node->right->bin, 2);
			ft_putstr_fd(E0M""BOLD, 2);
		}
		ft_puterror(" command not found\n"E0M, NULL);
		node->right->type = 0;
	}
	return (1);
}
