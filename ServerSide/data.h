#ifndef DATA_H
#define DATA_H

// Structures to represent Courses, Registrations, and Students
typedef struct {
    char classCode[10];
    char courseCode[10];
    char courseName[50];
    char weekDay[10];
    char amPm[10];
    char period[10];
    char weeks[50];
    char room[10];
} Course;

typedef struct {
    char studentID[10];
    char classCode[10];
} Registration;

typedef struct {
    char studentID[10];
    char password[20];
} Student;

// Function to load courses from file
void loadCourses(const char* filename, Course courses[], int *courseCount);

// Function to load registrations from file
void loadRegistrations(const char* filename, Registration registrations[], int *regCount);

// Function to load students from file
void loadStudents(const char* filename, Student students[], int *studentCount);



#endif
