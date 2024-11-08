#include <stdio.h>
#include <stdlib.h>
#include "connection.h"
#include "interface.h"


int main() {
    // Call function to connect to the server
    
    connectToServer();
    // displayLogoAndMenu();
    // Call function to communicate with the server
    //send message to server with an 1s interval
    startConvo();
    //Scan user input and send to server
    char input[100];
    while (1)
    {
        printf("Enter your choice: ");
        scanf("%s", input);
        sendMsgToServer(input);
    }

    // Close the connection when finished
    closeConnection();

    return 0;
}
