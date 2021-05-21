/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiglesia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 16:14:52 by jiglesia          #+#    #+#             */
/*   Updated: 2021/05/21 16:17:58 by jiglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

void	sh_exit(t_shell *sh)
{
	free_history(sh->history);
	free(sh->history_path);
	free(sh->events);
	ft_freetrie(&sh->ev);
	free(sh);
	exit(EXIT_SUCCESS);
}
