#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 
#include <arpa/inet.h>


int main(int argc, char const *argv[]) 
{ 
    int server_port = atoi(argv[1]); 
    int server_fd, client_socket, msg_val; 
    struct sockaddr_in client_address;
    struct sockaddr_in my_address; 
    //int addrlen = sizeof(client_address);
    socklen_t addrlen = sizeof(client_address);

    char buffer[1024] = {0};

    pid_t childpid;

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) 
    { 
        perror("socket failed"); 
        exit(1); 
    }

    printf("Server Socket is created.\n");

    memset(&my_address, '\0', sizeof(my_address));
    my_address.sin_family = AF_INET; 
    my_address.sin_addr.s_addr = INADDR_ANY; 
    my_address.sin_port = htons(server_port); 
       
    if (bind(server_fd, (struct sockaddr *)&my_address, sizeof(my_address)) < 0) 
    { 
        perror("bind failed\n"); 
        exit(1); 
    }
    printf("Bind to port %d\n", server_port);

    if (listen(server_fd, 3) < 0) 
    { 
        perror("listen failed\n"); 
        exit(1); 
    }  else {
        printf("Listening....\n");
    }
    

    while (1) {
        client_socket = accept(server_fd, (struct sockaddr *)&client_address, &addrlen);
        if (client_socket < 0)
        {
            exit(1);
        }
        printf("Connection accept: [%s, %d]\n", inet_ntoa(client_address.sin_addr), ntohs(client_address.sin_port));

        // create a process to handle multiple clients 
        if ((childpid = fork()) == 0)
        {
            close(server_fd);

            while (1)
            {
                read(client_socket, buffer, 1024);

                if (strcmp(buffer, ":exit") == 0) // disconnect a client
                {
                    printf("Disconnect: [%s, %d]\n", inet_ntoa(client_address.sin_addr), ntohs(client_address.sin_port));
                    break;
                }
                else
                {
                    printf("Message from [%s, %d]: %s\n", inet_ntoa(client_address.sin_addr), (int)ntohs(client_address.sin_port), buffer);
                    send(client_socket, buffer, strlen(buffer), 0);
                    printf("Echo message to [%s, %d]: %s\n", inet_ntoa(client_address.sin_addr), (int)ntohs(client_address.sin_port), buffer);
                    bzero(buffer, sizeof(buffer));
                }
            }
        }
    }

    close (client_socket);

    return 0;

    // if ((client_socket = accept(server_fd, (struct sockaddr *)&client_address, (socklen_t *)&addrlen)) < 0)
    // {
    //     perror("accept failed\n");
    //     exit(1);
    // }
    // msg_val = read(client_socket, buffer, 1024); 

    // printf("Message from [%s, %d]: %s\n", inet_ntoa(client_address.sin_addr), (int) ntohs(client_address.sin_port), buffer); 
    // send(client_socket , buffer , strlen(buffer) , 0 ); 
    // printf("Hello message sent\n"); 
} 
