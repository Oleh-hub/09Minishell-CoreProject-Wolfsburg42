/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beredzhe <beredzhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 21:09:59 by beredzhe          #+#    #+#             */
/*   Updated: 2024/07/01 21:17:36 by beredzhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ignore_ctrl_bslash(void)
{
	struct sigaction	sa;

	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa, NULL);
}

/*ctrl-backslash is ignored*/
void	sig_interactive(void)
{
	ignore_ctrl_bslash();
}
