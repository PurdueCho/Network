#include <stdio.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <unistd.h> 
#include <string.h> 
#include <stdlib.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(int argc, char const *argv[]) 
{
    const char *server_ip = argv[1];
    int server_port = atoi(argv[2]); 
    int my_socket = 0, msg_val; 
    struct sockaddr_in serv_addr; 

    char buffer[1024] = {0};

    if ((my_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
    { 
        printf("Socket creation error \n"); 
        exit(1); 
    }
    printf("Client Socket is created.\n");

    memset(&serv_addr, '\0', sizeof(serv_addr));
    serv_addr.sin_family = AF_INET; 
    serv_addr.sin_port = htons(server_port); 
       
    if(inet_pton(AF_INET, server_ip, &serv_addr.sin_addr)<=0)  
    { 
        printf("Invalid address\n"); 
        exit(1); 
    }

    if (connect(my_socket, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) 
    { 
        printf("Connection Failed \n"); 
        exit(1);
    }
    printf("Connected to Server.\n");

    while (1)
    {
        printf("Client message:    ");
        scanf("%s", &buffer[0]);
        send(my_socket, buffer, strlen(buffer), 0);

        if (strcmp(buffer, ":exit") == 0) // disconnect this client
        {
            close(my_socket);
            printf("Disconnected from server.\n");
            exit(1);
        }

        if (read(my_socket, buffer, 1024) < 0)
        {
            printf("Receive failed\n");
        }
        else
        {
            printf("Server message:    %s\n", buffer);
        }
    }

    return 0;

    // send(my_socket, hello_msg, strlen(hello_msg), 0); 
    // printf("Hello message sent\n"); 
    // msg_val = read(my_socket, buffer, 1024); 
    // printf("Message from server: %s\n", buffer); 
    // return 0; 
} 
