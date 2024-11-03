#include "define.h"
struct infomation *info = NULL;
bool battle_requestSignal = false;
pthread_mutex_t command_mutex = PTHREAD_MUTEX_INITIALIZER;
bool battlling_signal = false;

int server_fd = 0;
int main() {
    struct sockaddr_in server_addr;
    //pthread_cond_init(&command_cond, NULL);
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr(SERVER_IP);

    if (connect(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("Connection failed");
        exit(EXIT_FAILURE);
    }
    
    printf("Connected to server.\n");
    info = malloc(sizeof(struct infomation));
    info -> fd = server_fd;
    info -> name[0] = '\0';
    info -> rival[0] = '\0';
    
    loggin_to_server(server_fd);

    close(server_fd);
    //pthread_cond_destroy(&command_cond);
    return 0;
}

