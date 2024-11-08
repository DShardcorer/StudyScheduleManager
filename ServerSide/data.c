#include <stdio.h>
#include <string.h>
#include "data.h"
#include "utils.h"

// Function to load courses from file
void loadCourses(const char* filename, Course courses[], int *courseCount) {
    FILE *file = fopen(filename, "r");
    if (file != NULL) {
        char line[200]; // Adjust size if necessary
        while (fgets(line, sizeof(line), file)) {
            char *token;
            // Class code
            token = strtok(line, " ");
            strcpy(courses[*courseCount].classCode, token);


            // Course code
            token = strtok(NULL, " "); //strtok returns a pointer to the next token
            strcpy(courses[*courseCount].courseCode, token);




            // Course name (handle names with spaces)
            token = strtok(NULL, " ");
            char* lastToken = token;
            while((token = strtok(NULL, " ")) != NULL) {
                strcat(courses[*courseCount].courseName, " ");
                strcat(courses[*courseCount].courseName, lastToken);
                lastToken = token;
            }


            // Start time
            char temp[2];
            token = strtok(lastToken, ",");
            // courses[*courseCount].weekDay = token[0];
            // courses[*courseCount].amPm = token[1];
            // courses[*courseCount].periodStart = token[2];
            strcpy(courses[*courseCount].weekDay, weekDay(token[0]));
            strcpy(courses[*courseCount].amPm, amPm(token[1]));

            temp[0] = token[2];
            temp[1] = '\0';
            strcat(courses[*courseCount].period, temp);
            strcat(courses[*courseCount].period, "-");

            // End time
            token = strtok(NULL, ",");
            temp[0] = token[2];
            temp[1] = '\0';
            strcat(courses[*courseCount].period, temp);
            strcat(courses[*courseCount].period, "\0");



            // Weeks
            token = strtok(NULL, ",");
            lastToken = token;
            strcpy(courses[*courseCount].weeks, lastToken);
            token = strtok(NULL, ",");
            lastToken = token;
            
            while((token = strtok(NULL, ",")) != NULL) {
                strcat(courses[*courseCount].weeks, ",");
                strcat(courses[*courseCount].weeks, lastToken);
                lastToken = token;
            }



            //Room
            lastToken[sizeof(lastToken)-2] = '\0';
            strcpy(courses[*courseCount].room, lastToken);
            // Assign the last token found to the room

            // //print all
            // printf("classCode: %s\n", courses[*courseCount].classCode);
            // printf("courseCode: %s\n", courses[*courseCount].courseCode);
            // printf("courseName: %s\n", courses[*courseCount].courseName);
            // printf("weekDay: %s\n", courses[*courseCount].weekDay);
            // printf("amPm: %s\n", courses[*courseCount].amPm);
            // printf("period: %s\n", courses[*courseCount].period);
            // printf("weeks: %s\n", courses[*courseCount].weeks);
            // printf("room: %s\n", courses[*courseCount].room);
            // printf("\n");   
                (*courseCount)++;
        }

        fclose(file);
    } else {
        printf("Failed to open file: %s\n", filename);
    }
}


// Function to load registrations from file
void loadRegistrations(const char* filename, Registration registrations[], int *regCount) {
    FILE *file = fopen(filename, "r");
    if (file != NULL) {
        while (fscanf(file, "%s %s", 
                registrations[*regCount].studentID, 
                registrations[*regCount].classCode) == 2) {
            (*regCount)++;
        }
        fclose(file);
    } else {
        printf("Failed to open file: %s\n", filename);
    }
}

// Function to load students from file
void loadStudents(const char* filename, Student students[], int *studentCount) {
    FILE *file = fopen(filename, "r");
    if (file != NULL) {
        while (fscanf(file, "%s %s", 
                students[*studentCount].studentID, 
                students[*studentCount].password) == 2) {
            (*studentCount)++;
        }
        fclose(file);
    } else {
        printf("Failed to open file: %s\n", filename);
    }
}


