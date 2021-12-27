/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzarhou <mzarhou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 14:27:21 by mzarhou           #+#    #+#             */
/*   Updated: 2021/12/27 22:58:56 by mzarhou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include "utils.h"

char	g_char;

void	ft_handler(int p, siginfo_t *siginfo, void *_)
{
	static int	pid = -1;
	static int	shift_by = 7;

	_ = 0;
	if (pid != siginfo->si_pid && siginfo->si_pid != 0)
	{
		pid = siginfo->si_pid;
		shift_by = 7;
		g_char = 0;
	}
	if (p == SIGUSR2)
		g_char = g_char | (1 << shift_by);
	if (--shift_by < 0)
	{
		write(1, &g_char, 1);
		g_char = 0;
		shift_by = 7;
	}
	if (kill(pid, SIGUSR1) != 0)
		write(1, "Failed to send!\n", 17);
}

int	main(void)
{
	struct sigaction	disposition;

	g_char = 0;
	disposition.sa_flags = SA_SIGINFO;
	disposition.sa_sigaction = ft_handler;
	if (
		sigaction(SIGUSR1, &disposition, NULL) != 0
		|| sigaction(SIGUSR2, &disposition, NULL) != 0
	)
	{
		write(1, "sigaction error\n", 16);
		exit(1);
	}
	ft_putnbr_fd(getpid(), 1);
	while (1)
		pause();
}
