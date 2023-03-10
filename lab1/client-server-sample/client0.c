// Client side C/C++ program to demonstrate Socket
// programming
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#define PORT 12000

int main(int argc, char const* argv[])
{
	if (argc  != 1) {
		printf("Number of arguments provided shoudl be 1, not %d", argc);
		exit(-1)
	}
	char* ip_address = argv[0];
	char* port = argv[1];

	int sock = 0, valread, client_fd;
	struct sockaddr_in serv_addr;
	printf("Input lowercase sentence:\n");
	char sentence[256];
	fgets(sentence, sizeof(sentence), stdin);
	char modifiedSentence[1024] = { 0 };
	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		printf("\n Socket creation error \n");
		return -1;
	}

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(port);

	// Convert IPv4 and IPv6 addresses from text to binary
	// form
	if (inet_pton(AF_INET, ip_address, &serv_addr.sin_addr)
		<= 0) {
		printf(
			"\nInvalid address/ Address not supported \n");
		return -1;
	}

	if ((client_fd
		= connect(sock, (struct sockaddr*)&serv_addr,
				sizeof(serv_addr)))
		< 0) {
		printf("\nConnection Failed \n");
		return -1;
	}
	send(sock, sentence, strlen(sentence), 0);
	printf("Modified sentence received from server:\n");
	valread = read(sock, modifiedSentence, 1024);
	printf("%s\n", modifiedSentence);

	// closing the connected socket
	close(client_fd);
	return 0;
}
