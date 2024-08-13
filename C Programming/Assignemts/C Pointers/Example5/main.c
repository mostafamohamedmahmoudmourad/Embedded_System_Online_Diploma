/*
 * main.c
 *
 *  Created on: 15 Jul 2024
 *      Author: Mostafa Mourad
 *
 *  Ex5: Write a program in C to show a pointer to an array which contents are pointer to structure.
 */

#include <stdio.h>

// Define a structure for Employee
struct SEmployee {
    char *employee;  // Employee name
    int empid;       // Employee ID
};

int main() {
    // Initialize three employees
    static struct SEmployee emp1 = {"John", 1001}, emp2 = {"Alex", 1002}, emp3 = {"Taylor", 1003};

    // Create an array of pointers to the employees
    struct SEmployee *arr[] = {&emp1, &emp2, &emp3};

    // Create a pointer to the array of employee pointers
    struct SEmployee *(*pt)[3] = &arr;

    // Print the name and ID of the second employee
    printf("Employee Name: %s\n", (*pt)[1]->employee);
    printf("Employee ID: %d\n", (*pt)[1]->empid);

    return 0;
}

