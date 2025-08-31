
#include <iostream>

#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

int zport = 5432;

int main () {
	std::cout << "Starting ZDB" << std::endl;
	std::cout << "HI\n";

	int serverSocket = socket(AF_INET, SOCK_STREAM, 0);

	sockaddr_in serverAddress;
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_port = htons(zport);
	serverAddress.sin_addr.s_addr = INADDR_ANY;

	auto rc = bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress));
	if (rc == -1) {
		std::cout << "failed " << errno << std::endl;
		exit(1);
	}

	rc = listen(serverSocket, 5);
	if (rc == -1) {
		std::cout << "failed " << errno << std::endl;
		exit(1);
	}

	std::cout << "listen success" << std::endl;

	for (;;) {
		int clientSocket = accept(serverSocket, nullptr, nullptr);
		std::cout << "accepted cleint connection " << clientSocket << std::endl;

		char buffer[1024] = {0};
		recv(clientSocket, buffer, sizeof(buffer), 0);
		std::cout << "Message from client: " << buffer << std::endl;
	}
}
