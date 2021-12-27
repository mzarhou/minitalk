/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzarhou <mzarhou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 14:27:21 by mzarhou           #+#    #+#             */
/*   Updated: 2021/12/27 16:41:41 by mzarhou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdio.h>
#include <unistd.h>

char g_char;

void	handler(int p, siginfo_t *siginfo, void *_)
{
	static int shiftBy = 7;

	_ = 0;
	siginfo = 0;

	if (p == SIGUSR2)
		g_char = g_char | (1 << shiftBy);
	if (--shiftBy < 0) {
		write(1, &g_char, 1);
		g_char = 0;
		shiftBy = 7;
	}
}

int	main(void)
{
	g_char = 0;
	struct sigaction disposition;
	disposition.sa_flags = SA_SIGINFO;
	disposition.sa_sigaction	 = handler;
	sigaction(SIGUSR1, &disposition, NULL);
	sigaction(SIGUSR2, &disposition, NULL);

	printf("%d\n", getpid());
	while (1)
		pause();
}
