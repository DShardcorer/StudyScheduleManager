#ifndef CONNECTION_H
#define CONNECTION_H

#include "interface.h"
extern int listenfd;

void connectToServer();
void sendMsgToServer(const char *message);
void startConvo();
void closeConnection();

#endif