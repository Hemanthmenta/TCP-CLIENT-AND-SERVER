#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 8080
#define MAX_CONNECTIONS 5

int main() 
{
    int server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_size = sizeof(struct sockaddr_in);

    // Create socket
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) 
    {
        perror("Error creating socket");
        exit(EXIT_FAILURE);
    }

    // Set up server address struct
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    // Bind the socket
    if (bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) 
    {
        perror("Error binding socket");
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections or allowing 
    if (listen(server_socket, MAX_CONNECTIONS) == -1) 
    {
        perror("Error listening");
        exit(EXIT_FAILURE);
    }

    // Accept the connection
    client_socket = accept(server_socket, (struct sockaddr*)&client_addr, &addr_size);
    if (client_socket == -1) 
    {
        perror("Error accepting connection");
        exit(EXIT_FAILURE);
    }
    
    //recieve data from the client 
    char data[1024];
    recv(client_socket, data, sizeof(data), 0);
    printf("The recieved information from the client is : ");
    printf("%s\n", data);

    // Send data to the client
    char data1[20];
    printf("Enter the data to client server response : ");
    scanf("%s",data1);
    send(client_socket, data1, sizeof(data1), 0);
    

    // Close sockets
    close(client_socket);
    close(server_socket);

    return 0;
}

