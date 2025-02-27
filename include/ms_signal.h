/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_signal.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 02:26:34 by wchoe             #+#    #+#             */
/*   Updated: 2025/02/27 02:28:36 by wchoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_SIGNAL_H
# define MS_SIGNAL_H

extern int	ms_signal;

void	sigint_handler(int sig);
void	sig_handler_control(int sig);
void	sigquit_hanlder(int sig);
int	update_sigaction_interactive();
int	update_sigaction_control();
int	rollback_sigaction();
#endif
