#ifndef CONNECTION_H
#define CONNECTION_H

#include "auth.h"
#include "schedule.h"
#include "data.h"


extern int listenfd;
extern int connfd;


void createServerSocket(); // This one is not normally used. It is included in startServer() already.
void sendMsgToClient(const char* message);
char* receiveMsgFromClient();
void processMessage(const char* message, Course courses[], int courseCount, Registration registrations[], int regCount, Student students[], int studentCount);
void startServer(Course courses[], int courseCount, Registration registrations[], int regCount, Student students[], int studentCount);
void closeServer();


#endif