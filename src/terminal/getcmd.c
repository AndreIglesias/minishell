/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getcmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/16 21:08:33 by ciglesia          #+#    #+#             */
/*   Updated: 2021/05/20 23:57:55 by ciglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

/*
**	buf[4] up & dw have 3 chars + '\0'
**	up 27 91 65
**	dw 27 91 66
*/

void	input_handler(void)
{
	int		e;
	char	buf[4];
	ssize_t	len;

	while (!ft_strchr(buf, '\n'))
	{
		buf[0] = 0;
		len = read(STDIN_FILENO, buf, 3);
		buf[len] = 0;
		e = keys_event(buf);
		if (e)
			ft_putstr(buf);
		if (e == 1 && buf[0] != '\n')
		{
			g_sh->line = ft_strins(g_sh->line, buf, g_sh->line_cursor - 1);
			if (g_sh->line && g_sh->line_cursor < ft_strlen(g_sh->line))
			{
				ft_putstr_fd(g_sh->events->sc, 0);
				ft_putstr(&g_sh->line[g_sh->line_cursor]);
				ft_putstr_fd(g_sh->events->rc, 0);
			}
		}
	}
}

ssize_t	get_cmd(void)
{
	input_handler();
	if (g_sh->line && !g_sh->line[0])
	{
		free(g_sh->line);
		g_sh->line = NULL;
	}
	if (g_sh->line)
		save_cmdline(&g_sh->history, ft_strdup(g_sh->line));
	return (0);
}
