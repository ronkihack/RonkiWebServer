#include <winsock2.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#pragma comment( lib, "ws2_32.lib")

#define DEFAULT_PORT 8080
#define REQUEST_SIZE 4096

void error_die(const char* s)
{
	printf("%s", s);
}

int SendResponse(SOCKET sock)
{
	char buf[1024] = { 0 };
	int msg_len;

	//sprintf(header, "HTTP/1.1 200 OK\r\nContent-Type: %s; charset=UTF-8\r\n\r\n", get_content_type(rs->filename));
	send(sock, "HTTP/1.1 200 OK\r\nContent-Type: lala; charset=UTF-8\r\n\r\n", 54, 0);
	send(sock, "Helloaaaaa", 10, 0);
	//send(sock, "HTTP/1.1 500 Internal Server Error\r\nContent-Length: 0\r\n\r\n", 57, 0);

	return 1;
}

void *GetRequest(SOCKET sock)
{
	int msg_len;
	char buf[REQUEST_SIZE];

	msg_len = recv(sock, buf, sizeof(buf), 0);
	printf("Bytes Received: %d, message: %s from %s\n", msg_len, buf);

	return NULL;
}



void main()
{
	printf("Hello World\n");

	int addr_len;
	struct sockaddr_in local, client_addr;

	SOCKET sock, msg_sock;
	WSADATA wsaData;

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) == SOCKET_ERROR)
		error_die("WSAStartup()");

	// Fill in the address structure
	local.sin_family = AF_INET;
	local.sin_addr.s_addr = INADDR_ANY;
	local.sin_port = htons(DEFAULT_PORT);

	sock = socket(AF_INET, SOCK_STREAM, 0);

	if (sock == INVALID_SOCKET)
		error_die("socket()");

	if (bind(sock, (struct sockaddr *)&local, sizeof(local)) == SOCKET_ERROR)
		error_die("bind()");

listen_goto:

	if (listen(sock, 5) == SOCKET_ERROR)
		error_die("listen()");

	printf("Waiting for connection...\n");

	int count = 0;

	while (1)
	{
		addr_len = sizeof(client_addr);
		msg_sock = accept(sock, (struct sockaddr*)&client_addr, &addr_len);

		if (msg_sock == INVALID_SOCKET || msg_sock == -1)
			error_die("accept()");

		printf("\n\n#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$ %d\n\n", ++count);
		//printf("Connected to %s:%d\n", inet_ntoa(client_addr.sin_addr), htons(client_addr.sin_port));

		void *request = GetRequest(msg_sock);
		printf("Client requested");

		int sent = SendResponse(msg_sock);

		closesocket(msg_sock);

		if (sent == 0)
			break;
		else if (sent == -1)
			goto listen_goto;

	}

	WSACleanup();
}