/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_history.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiglesia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 19:30:05 by jiglesia          #+#    #+#             */
/*   Updated: 2021/05/18 19:01:28 by jiglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

static t_history	*init_history(void)
{
	t_history	*tmp;

	tmp = malloc(sizeof(t_history));
	if (!tmp)
		return (NULL);
	tmp->cmd = NULL;
	tmp->writen = 0;
	tmp->back = NULL;
	tmp->next = NULL;
	return (tmp);
}

void	save_cmdline(t_history **hst, char *line)
{
	(*hst)->back = init_history();
	(*hst)->back->cmd = line;
	line = NULL;
	(*hst)->back->next = (*hst);
	(*hst) = (*hst)->back;
}

static void	fill_history(int fd, t_history **hst)
{
	char	*line;
	int		i;

	i = HRY_SIZE;
	line = NULL;
	while (get_next_line(fd, &line) > 0 && i--)
	{
		save_cmdline(hst, line);
		(*hst)->writen = 1;
	}
	if (line)
		free(line);
	get_next_line(-1, &line);
	close(fd);
}

void	load_history(t_shell *sh)
{
	int	fd;

	fd = open(sh->history_path, O_RDONLY);
	if (fd > 0)
		fill_history(fd, &sh->history);
}

void	put_history_fd(t_history *hst, int fd)
{
	size_t		size;
	t_history	*tmp;

	tmp = hst;
	size = HRY_SIZE;
	while (size-- && tmp->next)
		tmp = tmp->next;
	while (tmp)
	{
		ft_putstr_fd(tmp->cmd, fd);
		ft_putchar_fd('\n', fd);
		tmp = tmp->back;
	}
}
