#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "schedule.h"

#define PERIODS 12
#define DAYS 5

// Function to display schedule for a specific day
char* readScheduleForDay(Course courses[], int courseCount, Registration registrations[], int regCount, char studentID[], char day[]) {
    // Allocate memory for the result string
    char* result = malloc(4096); // Adjust size as needed
    if (!result) {
        perror("Failed to allocate memory");
        return NULL;
    }

    strcpy(result, "=========================================================================================\n");
    strcat(result, "Code   | Course             | Week Day | AM/PM | Period | Weeks          | Room\n");
    strcat(result, "=========================================================================================\n");

    for (int i = 0; i < regCount; i++) {
        if (strcmp(registrations[i].studentID, studentID) == 0) {
            for (int j = 0; j < courseCount; j++) {
                if (strcmp(registrations[i].classCode, courses[j].classCode) == 0 && strcmp(courses[j].weekDay, day) == 0) {
                    char line[256]; // Temporary buffer for each line
                    snprintf(line, sizeof(line), "%s | %-18s | %-8s | %-4s  | %-5s | %-13s | %s\n", 
                             courses[j].courseCode, courses[j].courseName, courses[j].weekDay, 
                             courses[j].amPm, courses[j].period, courses[j].weeks, courses[j].room);
                    strcat(result, line); // Append the line to result
                }
            }
        }
    }
    strcat(result, "=========================================================================================\n");
    
    return result; // Return the result string
}

// Function to display schedule for the entire week
char* readScheduleForWeek(Course courses[], int courseCount, Registration registrations[], int regCount, char studentID[]) {
    char* result = malloc(4096); // Adjust size as needed
    if (!result) {
        perror("Failed to allocate memory");
        return NULL;
    }

    // Initialize the schedule array with empty strings
    char schedule[DAYS][PERIODS][20];  // 20 is enough to store the room string
    for (int i = 0; i < DAYS; i++) {
        for (int j = 0; j < PERIODS; j++) {
            strcpy(schedule[i][j], " ");  // Fill with spaces for formatting
        }
    }

    // Array to store the days of the week
    char* weekdays[] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday"};

    // Populate the schedule array with course data
    for (int i = 0; i < regCount; i++) {
        if (strcmp(registrations[i].studentID, studentID) == 0) {
            for (int j = 0; j < courseCount; j++) {
                if (strcmp(registrations[i].classCode, courses[j].classCode) == 0) {
                    for (int k = 0; k < DAYS; k++) {
                        if (strcmp(courses[j].weekDay, weekdays[k]) == 0) {
                            // Convert period range like "3-6" to individual periods
                            int startPeriod, endPeriod;
                            sscanf(courses[j].period, "%d-%d", &startPeriod, &endPeriod);

                            // Fill the schedule grid for each period in the range
                            for (int p = startPeriod - 1; p < endPeriod; p++) {
                                snprintf(schedule[k][p], 20, "%s", courses[j].room);
                            }
                        }
                    }
                }
            }
        }
    }

    // Build the result string
    strcpy(result, "=======================================================================================\n");
    strcat(result, "   |Monday    |Tuesday   |Wednesday |Thursday  |Friday    |\n");
    strcat(result, "---------------------------------------------------------------------------------------\n");

    for (int period = 0; period < PERIODS; period++) {
        char line[256]; // Temporary buffer for each line
        snprintf(line, sizeof(line), "%2d |", period + 1);
        strcat(result, line);
        for (int day = 0; day < DAYS; day++) {
            snprintf(line, sizeof(line), "%-10s|", schedule[day][period]);
            strcat(result, line);
        }
        strcat(result, "\n");
    }

    strcat(result, "=======================================================================================\n");
    
    return result; // Return the result string
}
