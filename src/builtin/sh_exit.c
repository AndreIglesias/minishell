/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/17 19:17:34 by ciglesia          #+#    #+#             */
/*   Updated: 2021/07/28 21:42:11 by ciglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

static int	ll_to_uchar(char *value)
{
	t_uchar		a;
	long long	tmp;

	tmp = ft_atoll(value);
	if (!tmp)
	{
		ft_putstr_fd(BOLD"minishell: exit: ", 2);
		ft_putstr_fd(value, 2);
		ft_putstr_fd(": numeric argument required\n"E0M, 2);
	}
	a = (t_uchar)tmp;
	return ((int)a);
}

static void	free_g_sh(void)
{
	if (g_sh->line_tmp)
		free(g_sh->line_tmp);
	if (g_sh->line)
		free(g_sh->line);
	if (g_sh->history)
		free_history(g_sh->history);
	if (g_sh->history_path)
		free(g_sh->history_path);
	if (g_sh->events)
		free(g_sh->events);
	if (g_sh->ev)
		ft_freetrie(&g_sh->ev);
	if (g_sh->envp)
		ft_freesplit(g_sh->envp);
	if (g_sh->cmd_line)
		free_cmd_line();
	if (g_sh->cmds)
		free_ast();
	if (g_sh)
		free(g_sh);
}

void	sh_exit(char *value)
{
	int	fd;
	int	exit_status;

	fd = open(g_sh->history_path, O_WRONLY | O_CREAT | O_TRUNC,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (fd != -1)
		put_history_fd(g_sh->history, fd);
	tcsetattr(0, 0, &g_sh->new_term);
	tgetent(NULL, "");
	exit_status = 0;
	if (value && value[0] != '0')
		exit_status = ll_to_uchar(value);
	if (fd == -1)
		ft_puterror(BOLD"minishell: ~/.minishell_history not generated\n"E0M, 0);
	free_g_sh();
	ft_putstr_fd(tgetstr("ve", NULL), 0);
	exit(exit_status);
}
