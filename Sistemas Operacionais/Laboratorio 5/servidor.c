#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <string.h>
#include <errno.h>

#define SOCKET_PATH "/tmp/laboratorio5a.sock"

void traduzir_servidor()
{
	int s, s2, t, len;

	struct sockaddr_un local, remote;
	char str[100];

	if ((s = socket(AF_UNIX, SOCK_STREAM, 0)) == -1) 	
	{
		perror("socket");
		exit(1);
	}

	memset(&local, 0, sizeof(local));
	local.sun_family = AF_UNIX;
	strncpy(local.sun_path, SOCKET_PATH, sizeof(local.sun_path) - 1);

	unlink(local.sun_path);

	len = strlen(local.sun_path) + sizeof(local.sun_family);

	if (bind(s, (struct sockaddr *)&local, len) == -1) 
	{
		perror("bind");
		exit(1);
	}

	if (listen(s, 5) == -1) 
	{
		perror("listen");
		exit(1);
	}

	while (1) 
	{
		int done, n;

		printf("Servidor esperando por conexões...\n");

		t = sizeof(remote);
		if ((s2 = accept(s, (struct sockaddr *)&remote, &t)) == -1) 
		{
			perror("accept");
			exit(1);
		}
		printf("Conexão aceita.\n");
		done = 0;

		do 
		{
			n = recv(s2, str, 100, 0);
			if (n <= 0) {
				if (n < 0)
					perror("recv");
				done = 1;
			}
			if (!done) 
			{
				str[n] = '\0';
				
				printf("Cliente diz: %s\n", str);
				
				char origem[3];
				char destino[3];
				char palavra[50];
				
				sscanf(str, "%2s-%2s:%s", origem, destino, palavra);

				printf("Origem: %s\nDestino: %s\nPalavra: %s\n", origem, destino, palavra);
				if (strcmp(palavra, "NO-NO") == 0) 
				{
					printf("Conexão encerrada pelo cliente.\n");
					done = 1;
				}
				else 
				{
					char resposta[100];
                    if(strcmp(origem, "pt") == 0 && strcmp(destino, "en") == 0 && strcmp(palavra, "cachorro") == 0) 
					{
                        strcpy(resposta, "dog");
					}
					if(send(s2, resposta, strlen(resposta), 0) == -1) 
					{
						perror("send");
						done = 1;
					}
				}
			}
		} 
		while (!done);

		close(s2);
	}
}


int main()
{
	traduzir_servidor();

	return 0;
}
