#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void sendBit(int bit, int serverPid)
{
	if (bit == 0)
		kill(serverPid, SIGUSR1);
	else
		kill(serverPid, SIGUSR2);
}

void	sendChar(char c, int serverPid)
{
	int bit;
	int	shiftBy;

	shiftBy = 7;
	while (shiftBy >= 0)
	{
		bit = 1 & (c >> shiftBy);
		sendBit(bit, serverPid);
		usleep(200);
		shiftBy--;
	}
}

int	main(int argc, char **argv)
{
	char	*serverPid;
	char	*stringToSend;

	if (argc != 3)
		return (1);
	serverPid = argv[1];
	stringToSend = argv[2];

	while (*stringToSend)
	{
		sendChar(*stringToSend, atoi(serverPid));
		stringToSend++;
	}
}
