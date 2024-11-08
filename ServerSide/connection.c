#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <ctype.h>
#include <sys/wait.h>
#include "connection.h"

// Procedure: socket() -> bind() -> listen() -> accept() -> recv() -> send() -> close()

#define MAXLINE 4096   /* max text line length */
#define SERV_PORT 3000 /* port */
#define LISTENQ 8      /* maximum number of client connections */
#define INET_ADDRSTRLEN 16


pid_t pid;
int listenfd; // Global variable for the listening file descriptor
int connfd;   // Global variable for the connection file descriptor


void sig_chld(int signo)
{
pid_t pid;
int stat;
while ( (pid = waitpid(-1, &stat, WNOHANG)) > 0)
printf("child %d terminated\n", pid);
return;
}
/*
WNOHANG: waitpid does not block
while loop: waitpid repeatedly until there is no child
process change status, i.e until waitpid returns 0.
*/


// Function to create and set up the server socket
void createServerSocket()
{
    struct sockaddr_in servaddr;

    // Create the socket and assign it to the global variable
    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if (listenfd < 0)
    {
        perror("Socket creation failed");
        exit(1);
    }

    // Prepare the server address structure
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(SERV_PORT);

    // Bind the socket to the address
    if (bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
    {
        perror("Bind failed");
        exit(1);
    }

    // Start listening for connections
    if (listen(listenfd, LISTENQ) < 0)
    {
        perror("Listen failed");
        exit(1);
    }

    printf("Server created and listening on port %d...\n", SERV_PORT);
}

// Function to handle individual client connections
void sendMsgToClient(const char *message)
{
        send(connfd, message, strlen(message), 0);
    // Close the connection after serving the client
}

// Infinite loop to display client's messages:
char *receiveMsgFromClient() {
    char buf[MAXLINE];
    int n;

    while (1) {
        n = recv(connfd, buf, MAXLINE - 1, 0); // Attempt to receive data

        if (n > 0) {
            buf[n] = '\0'; // Null-terminate the received string
            char *message = malloc(strlen(buf) + 1); // Allocate memory for the string
            if (message == NULL) {
                perror("Memory allocation failed");
                exit(EXIT_FAILURE);
            }
            strcpy(message, buf); // Copy the received message to the allocated memory
            return message; // Return the dynamically allocated string
        }

        if (n < 0) {
            perror("Read error");
            return NULL; // Return NULL on error
        }

        sleep(0.1); // Sleep for 1 second before trying again (uncomment if desired)
    }
}
// Main server loop to accept and handle client connections
void startServer(Course courses[], int courseCount, Registration registrations[], int regCount, Student students[], int studentCount)
{
    createServerSocket(); // Create the server socket
    socklen_t clilen;
    struct sockaddr_in cliaddr;
    char cliAddrStr[INET_ADDRSTRLEN];

    printf("Server running...waiting for connections.\n");

    for (;;)
    {
        clilen = sizeof(cliaddr);

        // Accept a connection from the client
        connfd = accept(listenfd, (struct sockaddr *)&cliaddr, &clilen);
        if (connfd < 0)
        {
            perror("Accept failed");
            continue; // Continue to accept other connections
        }
        if( (pid = fork()) == 0){
            close(listenfd);
            // Print client's information
        printf("Connection from %s, port %d\n",
               inet_ntop(AF_INET, &cliaddr.sin_addr, cliAddrStr, INET_ADDRSTRLEN),
               ntohs(cliaddr.sin_port));

        // Handle the client messages
        while (1)
        {
            char *message = receiveMsgFromClient(); // Receive the message
            if (message == NULL)
            {
                break; // Break if no message was received
            }
            processMessage(message, courses, courseCount, registrations, regCount, students, studentCount); // Process the received message
            // Process the received message
            free(message); // Free the allocated memory for the message
        }
        close(connfd); // Close the connection for the current client
        }
        signal(SIGCHLD,sig_chld);
        close(connfd); /* parent closes connected socket */
        
        
    }
}

void processMessage(const char *message, Course courses[], int courseCount, Registration registrations[], int regCount, Student students[], int studentCount)
{
    printf("Received message: %s\n", message);
    if (strcmp(message, "exit") == 0)
    {
        closeServer();
    }

    if (strcmp(message, "login") == 0)
    {
        char studentID[10];
        if ((strcpy(studentID, processLogin(students, studentCount))) != NULL)
        {
            while (1)
            {
                sleep(1);
                sendMsgToClient("Enter a day of the week or 'ALL' to display the full schedule: ");
                char *day = receiveMsgFromClient();

                for (int i = 0; day[i]; i++)
                {
                    day[i] = tolower(day[i]);
                }
                day[0] = toupper(day[0]);
                if (strcmp(day, "All") == 0)
                {
                    sendMsgToClient(readScheduleForWeek(courses, courseCount, registrations, regCount, studentID));
                }
                else if (strcmp(day, "Exit") == 0)
                {
                    printf("Exiting program. Goodbye!\n");
                    break;
                }
                else if (strcmp(day, "Monday") == 0 || strcmp(day, "Tuesday") == 0 || strcmp(day, "Wednesday") == 0 || strcmp(day, "Thursday") == 0 || strcmp(day, "Friday") == 0)
                {
                    sendMsgToClient(readScheduleForDay(courses, courseCount, registrations, regCount, studentID, day));
                }
                else
                {
                    sendMsgToClient("Invalid input. Try again.");
                }
                free(day);
            }
        }
    }
}

// Function to close the server socket
void closeServer()
{
    close(connfd);
    close(listenfd);
    printf("Server closed.\n");
    exit(0);
}
