#ifndef SCHEDULE_H
#define SCHEDULE_H

#include "data.h"
// Function to display schedule for a specific day
char* readScheduleForDay(Course courses[], int courseCount, Registration registrations[], int regCount, char studentID[], char day[]);

// Function to display schedule for the entire week
char* readScheduleForWeek(Course courses[], int courseCount, Registration registrations[], int regCount, char studentID[]);

#endif
