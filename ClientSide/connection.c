#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include "connection.h"

#define MAXLINE 4096 /* max text line length */
#define SERV_PORT 3000 /* port */

int sockfd; // Make this global or pass it around between functions

// Function to establish the connection to the server
void connectToServer() {
    struct sockaddr_in servaddr;
    char *serveripaddress = "127.0.0.1"; // Define the server IP

    // Create a socket for the client
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Problem in creating the socket");
        exit(2);
    }

    // Initialize the server address struct
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr(serveripaddress);
    servaddr.sin_port = htons(SERV_PORT);

    // Attempt to connect to the server
    if (connect(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr)) < 0) {
        perror("Problem in connecting to the server");
        exit(3);
    }

    printf("Connected to the server at %s on port %d.\n", serveripaddress, SERV_PORT);
}

// Function to send and receive messages
// Function to send a given message to the server and receive the response
void sendMsgToServer(const char *message) {
    char recvline[MAXLINE];

    // Send the provided message to the server
    sleep(1);
    send(sockfd, message, strlen(message), 0);

    // // Receive a response from the server
    // if (recv(sockfd, recvline, MAXLINE, 0) == 0) {
    //     perror("The server terminated prematurely");
    //     exit(4);
    // }

    // // Print server response
    // printf("String received from the server: ");

    // // Check if the message is "exit" to close the connection
    // if (strncmp(message, "exit", 4) == 0) {
    //     printf("Exiting...\n");
    //     closeConnection();
    // }
}
void startConvo() {
    char sendline[MAXLINE];
    char recvline[MAXLINE];

    while (1) {
        // Prompt user for input
        if (fgets(sendline, MAXLINE, stdin) != NULL) {
            // Remove the newline character if present
            sendline[strcspn(sendline, "\n")] = 0; // Remove newline

            // Send the provided message to the server
            send(sockfd, sendline, strlen(sendline), 0);

            // Check if the message is "exit" to close the connection
            if (strcmp(sendline, "exit") == 0) {
                printf("Exiting...\n");
                close(sockfd);
                exit(0);
            }

            // Loop until a response is received
            while (1) {
                int n = recv(sockfd, recvline, MAXLINE - 1, 0);
                if (n > 0) {
                    recvline[n] = '\0'; // Null-terminate the received string

                    if(strcmp(recvline, "Login successful.") == 0) {
                        displayLogoAndMenu();
                    }
                    printf("%s\n", recvline);
                    break; // Break the loop after receiving a valid response
                } else if (n < 0) {
                    perror("Error receiving from server");
                    break; // Exit the loop on error
                }
                // Optional: add a timeout or other condition here if needed
            }
        }
    }
}







// Function to close the connection to the server
void closeConnection() {
    close(sockfd);
    printf("Connection closed.\n");
}

