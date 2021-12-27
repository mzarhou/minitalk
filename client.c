/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzarhou <mzarhou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 22:27:20 by mzarhou           #+#    #+#             */
/*   Updated: 2021/12/27 22:59:45 by mzarhou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include "utils.h"

int	g_done = 1;

void	ft_handler(int sig)
{
	sig = 0;
	g_done = 1;
}

void	ft_send_bit(int bit, int server_pid)
{
	int	kill_ret;

	if (bit == 0)
		kill_ret = kill(server_pid, SIGUSR1);
	else
		kill_ret = kill(server_pid, SIGUSR2);
	if (kill_ret != 0)
	{
		write(1, "Failed to send!\n", 17);
		exit(1);
	}
}

void	ft_send_char(char c, int server_pid)
{
	int	bit;
	int	shift_by;

	shift_by = 7;
	while (shift_by >= 0)
	{
		while (!g_done)
			usleep(10);
		g_done = 0;
		bit = 1 & (c >> shift_by);
		ft_send_bit(bit, server_pid);
		shift_by--;
	}
}

int	main(int argc, char **argv)
{
	int		server_pid;
	char	*string_to_send;

	if (argc != 3)
		return (1);
	server_pid = ft_atoi(argv[1]);
	string_to_send = argv[2];
	signal(SIGUSR1, ft_handler);
	signal(SIGUSR2, ft_handler);
	while (*string_to_send)
	{
		ft_send_char(*string_to_send, server_pid);
		string_to_send++;
	}
}
