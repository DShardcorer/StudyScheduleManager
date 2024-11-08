#include <string.h>
#include <stdlib.h>
#include "auth.h" // "" for local header file, <> for system header file


// Function to check login credentials
int login(Student students[], int studentCount, char studentID[], char password[]) {
    for (int i = 0; i < studentCount; i++) {
        if (strcmp(students[i].studentID, studentID) == 0 && strcmp(students[i].password, password) == 0) {
            return 1;
        }
    }
    return 0;
}

char* processLogin(Student students[], int studentCount) {
    printf("Processing login...\n");
    sendMsgToClient("Enter Student ID: ");
    char studentID[10];
    strcpy(studentID, receiveMsgFromClient());
    sendMsgToClient("Enter Password: ");
    char password[20];
    strcpy(password, receiveMsgFromClient());

    if (login(students, studentCount, studentID, password)) {
        sendMsgToClient("Login successful.");
        char* result = malloc(strlen(studentID) + 1); // Allocate memory for studentID
        if (result != NULL) {
            strcpy(result, studentID); // Copy to allocated memory
        }
        return result; // Return the allocated memory
    } else {
        sendMsgToClient("Invalid login, Try again? (y/n)");
        char response[2];
        strcpy(response, receiveMsgFromClient());
        if (strcmp(response, "y") == 0) {
            return processLogin(students, studentCount);
        } else {
            sendMsgToClient("Exiting...");
            closeServer();
            return NULL; // Return NULL if exiting
        }
    }
}
