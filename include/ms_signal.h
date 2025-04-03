/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_signal.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 02:26:34 by wchoe             #+#    #+#             */
/*   Updated: 2025/03/21 13:03:27 by wchoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_SIGNAL_H
# define MS_SIGNAL_H

extern int	g_ms_signal;

void	sigint_handler(int sig);
void	sig_handler_control(int sig);
void	sigquit_hanlder(int sig);
int		update_sigaction_interactive(void);
int		update_sigaction_control(void);
int		rollback_sigaction(void);
#endif
