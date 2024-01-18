#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 8080//by using port number we can transfer or establish a connection

int main() 
{
    int tcp_socket;
    struct sockaddr_in server_addr;

    // Create socket
    tcp_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (tcp_socket == -1) 
    {
        perror("Error creating socket");
        exit(EXIT_FAILURE);
    }

    // Set up server address struct
    //memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;  

    // Connect to the server
    if (connect(tcp_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) 
    {
        perror("Error connecting to server");
        exit(EXIT_FAILURE);
    }

    
    //sending data to server
    char data[20];
    printf("Enter the data to server : ");
    scanf("%s",data);
    send(tcp_socket, data, sizeof(data), 0);
    
    //recieving data from server
    char data1[1024];
    printf("The receieved informatin from the server is : ");
    recv(tcp_socket, data1, sizeof(data1), 0);
    printf("%s\n", data1);
    
    

    // Close socket
    close(tcp_socket);

    return 0;
}

