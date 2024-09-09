# Memory Management Student Courses

This repository contains a C program that demonstrates the use of dynamically allocated linked lists to manage students and courses. The program includes functionality for adding students and courses, registering and unregistering students for courses, printing reports, and releasing allocated memory.

## Overview

The assignment focuses on implementing linked lists and dynamic memory management in C. The program handles student and course data using linked lists and provides functions for managing registrations, printing reports, and freeing memory to avoid leaks.

## Structures

The program uses the following structures to represent students and courses:

```c
typedef struct student {
    char *name;
    int id;
    struct clist *courses;
} student;

typedef struct course {
    char *title;
    int number;
    struct slist *students;
} course;

typedef struct slist {
    student *info;
    struct slist *next;
} slist;

typedef struct clist {
    course *info;
    struct clist *next;
} clist;

- **student**: Contains the student's name, ID, and a list of courses the student is registered for.
- **course**: Contains the course title, number, and a list of students registered for the course.
- **slist**: Linked list node for students.
- **clist**: Linked list node for courses.

## Basic Operations

### 1. Adding Students and Courses

- These functions add a new student or course to the respective list. Memory is allocated dynamically for the new student or course, and strings are copied to avoid memory management issues.

### 2. Registration and Unregistration

- **reg_student**: Registers a student for a course by updating both the student's and course's linked lists.
- **unreg_student**: Unregisters a student from a course by removing the student from the course's student list.

### 3. Printing Reports

- **print_students**: Prints all students with their ID, name, and list of courses, ordered by student ID and course number.
- **print_courses**: Prints all courses with their number, title, and list of students, ordered by course number and student ID.

### 4. Releasing Memory

- This function releases all dynamically allocated memory for the student and course lists. It ensures that there are no memory leaks by freeing both the linked list nodes and the dynamically allocated strings.

## Main Function

- The `main` function handles user input and invokes the functions that were implemented for adding students, courses, registration, unregistration, printing reports, and freeing memory.

## Compilation and Execution

### 1. Compile the Program:

```bash
gcc -o memory_allocation main.c

### 2. Run the Program:

To execute the program, use the following command:

```bash
./memory_allocation

### 3. Check for Memory Leaks:

To check for memory leaks, you can use valgrind with the following command:

```bash
valgrind --leak-check=full ./memory_allocation
