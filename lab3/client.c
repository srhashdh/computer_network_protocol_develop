#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 8080
#define SERVER_IP "192.168.8.185"
#define TOTAL_CONNECTIONS 1000000

int main(){
	int *sock = (int *)malloc(sizeof(int) * TOTAL_CONNECTIONS);
	struct sockaddr_in serv_addr;
	serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    serv_addr.sin_addr.s_addr = inet_addr(SERVER_IP);


	for(int i = 0; i < TOTAL_CONNECTIONS; i++){
		sock[i] = socket(AF_INET, SOCK_STREAM, 0);
		if(sock[i] == -1){
			printf("\n Socket creation error %d\n", i);
			return -1;
		}
		
		if(connect(sock[i], (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1){
			printf("\nConnection Failed\n");
			return -1;
		}
		printf("%d success\n", i);
	}
	return 0;
}

	
	