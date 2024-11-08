#include <stdio.h>
#include <string.h>
#include "auth.h"
#include "schedule.h"
#include "data.h"
#include "utils.h"
#include "connection.h"

// Function to display graphical logo and instruction menu

int main() {
    Course courses[100];
    Registration registrations[100];
    Student students[100];

    int courseCount = 0, regCount = 0, studentCount = 0;

    // Display logo and instruction menu
    // Load data from files
    loadCourses("database/course_schedule.txt", courses, &courseCount);
    loadRegistrations("database/student_registration.txt", registrations, &regCount);
    loadStudents("database/user_account.txt", students, &studentCount);


    //pass the data to the server
    startServer(courses, courseCount, registrations, regCount, students, studentCount);



    // // Login process
    // char studentID[10], password[20];
    // printf("Enter Student ID: ");
    // scanf("%s", studentID);
    // printf("Enter Password: ");
    // scanf("%s", password);

    // if (login(students, studentCount, studentID, password)) {
    //     while (1) {
    //         char day[10];
    //         printf("Enter a day of the week or 'ALL' to display the full schedule: ");
    //         scanf("%s", day);

    //         if (strcmp(day, "ALL") == 0) {
    //             readScheduleForWeek(courses, courseCount, registrations, regCount, studentID);
    //         } else if (strcmp(day, "EXIT") == 0) {
    //             printf("Exiting program. Goodbye!\n");
    //             break;
    //         } else {
    //             readScheduleForDay(courses, courseCount, registrations, regCount, studentID, day);
    //         }
    //     }
    // } else {
    //     printf("Invalid login.\n");
    // }

    return 0;
}
