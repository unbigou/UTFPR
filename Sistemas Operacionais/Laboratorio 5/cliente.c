#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>

#define SOCKET_PATH "/tmp/laboratorio5a.sock"

void traduzir_cliente()
{
    struct sockaddr_un server_address;
    int bytes_sent, bytes_received;

    char buffer[256];

    int socket_fd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (socket_fd == -1)
    {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    memset(&server_address, 0, sizeof(server_address));
    server_address.sun_family = AF_UNIX;
    strncpy(server_address.sun_path, SOCKET_PATH, sizeof(server_address.sun_path)-1);

    if(connect(socket_fd, (struct sockaddr*)&server_address, sizeof(server_address)) == -1) 
    {
        perror("connect");
        exit(EXIT_FAILURE);
    }

    while (1) 
    {
        printf("Digite a palavra a ser traduzida (NO-NO para sair): ");
        fgets(buffer, sizeof(buffer), stdin);
        buffer[strcspn(buffer, "\n")] = '\0';

        bytes_sent = send(socket_fd, buffer, strlen(buffer), 0);
        if (bytes_sent == -1) 
        {
            perror("send");
            exit(EXIT_FAILURE);
        }

        if(strcmp(buffer, "NO-NO") == 0) 
        {
            break;
        }

        bytes_received = recv(socket_fd, buffer, sizeof(buffer)-1, 0);
        if(bytes_received == -1) 
        {
            perror("recv");
            exit(EXIT_FAILURE);
        }

        buffer[bytes_received] = '\0';

        printf("Tradução: %s\n", buffer);
    }
    close(socket_fd);
}

int main() 
{
    traduzir_cliente();

    return 0;
}
