#define WIN32_LEAN_AND_MEAN
#define _WIN32_WINNT 0x501

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <winsock2.h>

#define SA struct sockaddr
#define MAXLINE 128
#define SERV_PORT 54000

void errexit(const char *format, ...)
{
	va_list	args;

	va_start(args, format);
	vfprintf(stderr, format, args);
	va_end(args);
	WSACleanup();
	exit(1);
}

void str_cli(SOCKET sockfd)
{
	char sendline[MAXLINE+1], recvline[MAXLINE+1];
	int	cc, n_out, n_in;

	while (fgets(sendline, MAXLINE, stdin) != NULL) 
	{
		sendline[MAXLINE] = '\0';  /* ensure line null-termination	*/
		n_out = strlen(sendline);

		// send out the data of n_out bytes
		send(sockfd, sendline, n_out, 0); 
		
		// receive n_out bytes of data from server
		for (n_in = 0; n_in < n_out; n_in += cc)
		{
			cc = recv(sockfd, &recvline[n_in], n_out - n_in, 0);
			if (cc == SOCKET_ERROR)
				errexit("socket recv failed: %d\n", WSAGetLastError());
		}
		recvline[n_in] = '\0';
		fputs(recvline, stdout);
	}
	closesocket(sockfd);
}

int main(int argc, char *argv[])
{
	SOCKET sockfd;
	struct sockaddr_in servaddr;
	WSADATA	wsadata;

	if (WSAStartup(MAKEWORD(2,2), &wsadata) != 0)
		errexit("WSAStartup failed\n");

	if (argc != 2)
		errexit("usage: tcpEchoCli01 <IPaddress>");

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd == INVALID_SOCKET)
		errexit("cannot create socket: error number %d\n", WSAGetLastError());

	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(SERV_PORT);
	if ( (servaddr.sin_addr.s_addr = inet_addr(argv[1])) == INADDR_NONE)
		errexit("inet_addr error: error number %d\n", WSAGetLastError());

	if (connect(sockfd, (SA *) &servaddr, sizeof(servaddr)) < 0)
		errexit("connect error: error number %d\n", WSAGetLastError());
	
	str_cli(sockfd);
	
	WSACleanup();
	exit(0);
}