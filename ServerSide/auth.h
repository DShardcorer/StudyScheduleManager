#ifndef AUTH_H 
#define AUTH_H

#include "data.h"
#include "connection.h"


// Function to authenticate user
int login(Student students[], int studentCount, char studentID[], char password[]);
char* processLogin();

#endif
