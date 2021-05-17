/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 18:08:10 by ciglesia          #+#    #+#             */
/*   Updated: 2021/05/17 20:59:05 by ciglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSH_H
# define MSH_H

# include "libft.h"

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <errno.h>
# include <string.h>
# include <signal.h>
# include <dirent.h>
# include <termios.h>
# include <curses.h>
# include <term.h>
# include <termcap.h>

# define BOLD "\e[1m"
# define DIM "\e[2m"
# define ITALIC "\e[3m"
# define UNDERL "\e[4m"
# define BLINK "\e[5m"
# define REVER "\e[7m"
# define INVIS "\e[8m"
# define RED "\e[38;2;255;0;0m"
# define CEL "\e[38;2;114;159;207m"
# define GREEN "\e[92m"
# define CYAN "\e[96m"
# define BLUE "\e[34m"
# define YELLOW "\e[33m"
# define ERROR "\e[38;2;255;0;0m\e[1mERROR\e[0m\e[38;2;255;0;0m"
# define BLACKB "\e[40m"
# define GRAY "\e[90m"
# define E0M "\e[0m"

# define MINERR "\e[38;2;255;0;0m\e[5mminishell: "

typedef struct s_envar
{
	char			*key;
	char			*value;
	t_uchar			set;
	struct s_envar	*next;
}	t_envar;

typedef struct s_events
{
	char	*ks;
	char	*up;
	char	*dw;
	char	*rg;
	char	*lf;
	char	*sc;
	char	*rc;
	char	*dc;
	char	*ce;
}	t_events;

typedef struct s_shell
{
	struct termios	old_term;
	struct termios	new_term;
	char			*history_path;
	char			*line;
	t_trie			*ev;
	t_events		*events;
}	t_shell;

/*
**  signal_handler
*/

void		sigint_shell(int sig);
void		sigquit_shell(int sig);

/*
**	terminal
*/

t_shell		*ft_shell(void);
void		store_envar(t_shell *sh, char **ev);
ssize_t		get_cmd(t_shell *sh);
void		keys_event(char *buf);

#endif