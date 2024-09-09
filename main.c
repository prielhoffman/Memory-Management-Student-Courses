/*   Priel Hoffman 318277308   */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// structures
typedef struct student {
    char* name;
    int  id;
    struct clist* courses;
} student;

typedef struct course {
    char* title;
    int  number;
    struct slist* students;
} course;

typedef struct slist {
    student* info;
    struct slist* next;
} slist;

typedef struct clist {
    course* info;
    struct clist* next;
} clist;


// prototypes
slist* add_student(slist* students, char* name, int id);
clist* add_course(clist* courses, char* title, int number);
void reg_student(slist* students, clist* courses, int id, int number);
void unreg_student(slist* students, int id, int number);
clist* remove_course(clist* coursesOfStudent, course* courseInfo);
slist* remove_student(slist* students, student* studentInfo);
void print_students(slist* students);
void print_courses(clist* courses);
void free_all(slist* sl, clist* cl);

//DO NOT TOUCH THIS FUNCTION
static void getstring(char* buf, int length) {
    int len;
    buf = fgets(buf, length, stdin);
    len = (int)strlen(buf);
    if (buf[len - 1] == '\n')
        buf[len - 1] = '\0';
}

//DO NOT TOUCH THIS FUNCTION 
int main() {
    slist* students = 0;
    clist* courses = 0;
    char  c;
    char  buf[100];
    int   id, num;

    do {
        printf("Choose:\n"
            "    add (s)tudent\n"
            "    add (c)ourse\n"
            "    (r)egister student\n"
            "    (u)nregister student\n"
            "    (p)rint lists\n"
            "    (q)uit\n");

        while ((c = (char)getchar()) == '\n');
        getchar();

        switch (c) {
        case 's':
            printf("Adding new student.\n");

            printf("Student name: ");
            getstring(buf, 100);

            printf("Student ID: ");
            scanf("%d", &id);

            students = add_student(students, buf, id);

            break;

        case 'c':
            printf("Adding new course.\n");

            printf("Course name: ");
            getstring(buf, 100);

            printf("Course number: ");
            scanf("%d", &num);

            courses = add_course(courses, buf, num);

            break;

        case 'r':
            printf("Registering a student to a course.\n");

            printf("Student ID: ");
            scanf("%d", &id);

            printf("Course number: ");
            scanf("%d", &num);

            reg_student(students, courses, id, num);

            break;

        case 'u':
            printf("Unregistering a student from a course.\n");

            printf("Student ID: ");
            scanf("%d", &id);

            printf("Course number: ");
            scanf("%d", &num);

            unreg_student(students, id, num);

            break;

        case 'p':
            printf("Printing Information.\n");

            print_students(students);
            print_courses(courses);

            break;

        case 'q':
            printf("Quitting...\n");
            break;
        }

        if (c != 'q')
            printf("\n");
    } while (c != 'q');

    free_all(students, courses);
    return 0;
}


/* This function receive a list of students, and add a new student to this list.
   The order in the list will be by the student's ID from low to high*/
slist* add_student(slist* students, char* name, int id) {
    slist* currStudent = students;
    slist* newStudent = (slist*)malloc(sizeof(slist));   //allocate memory for node
    if (newStudent == NULL) {
        printf("Memory allocation error!\n");
        exit(1);
    }
    newStudent->info = (student*)malloc(sizeof(student));   //alocate memory for node->info
    if (newStudent->info == NULL) {
        printf("Memory allocation error!\n");
        exit(1);
    }
    newStudent->info->id = id;
    newStudent->info->name = (char*)malloc(sizeof(char) * (strlen(name) + 1));
    if (newStudent->info->name == NULL) {
        printf("Memory allocation error!\n");
        exit(1);
    }
    strcpy(newStudent->info->name, name);
    newStudent->next = NULL;
    newStudent->info->courses = NULL;
    if (!students) {   //if the list of courses is empty we want to add the first course
        //We would like to allocate space in memory for node in the linked list and space in memory for more info about a course
        students = newStudent;
    }
    else {
        if (students->info->id > id) {
            newStudent->next = students;
            students = newStudent;
        }
        else{
            currStudent = students;
            while (currStudent->next && currStudent->next->info->id < id) {       //we want to point to last node
                currStudent = currStudent->next;
            }
            newStudent->next = currStudent->next;
            currStudent->next = newStudent;
        }  
    }
    return students;   
}






/* This function receive a list of courses, and add a new course to this list. */
clist* add_course(clist* courses, char* title, int number) {
    clist* currentCourse;
    clist* newCourse= (clist*)malloc(sizeof(clist));
    if (newCourse == NULL) {
        printf("Memory allocation error!\n");
        exit(1);
    }
    newCourse->info = (course*)malloc(sizeof(course));
    if (newCourse->info == NULL) {
        printf("Memory allocation error!\n");
        exit(1);
    }
    newCourse->next = NULL;
    newCourse->info->title = (char*)malloc(sizeof(char) * (strlen(title) + 1));
    if (newCourse->info->title == NULL) {
        printf("Memory allocation error!\n");
        exit(1);
    }
    strcpy(newCourse->info->title, title);
    newCourse->info->number = number;
    newCourse->info->students = NULL;
    if (!courses) {   //if the list of courses is empty we want to add the first course
        //We would like to allocate space in memory for node in the linked list and space in memory for more info about a course
        courses = newCourse;
    }
    else{
        if (courses->info->number > number) {
            newCourse->next = courses;
            courses = newCourse;
        }
        else {
            currentCourse = courses;
            while (currentCourse->next && currentCourse->next->info->number < number) {       //we want to point to last node
                currentCourse = currentCourse->next;
            }
            newCourse->next = currentCourse->next;
            currentCourse->next = newCourse;
        }
    }
    return courses;
}





/* This function receives the list of students, the list of courses, a student ID, and a course number
, and registers the student to the course*/
void reg_student(slist* students, clist* courses, int id, int number) {
    slist* pStudent = students, * currStudent=students;   //This will point a student's node in slist
    clist* pCourse = courses, * currentCourse=courses;    //This will point a course's node in clist
    student* student4registration;   //This will point student's info in slist
    course* course2register;   //This will point course's info in clist
    while (pStudent && pStudent->info->id != id) {   //from the beginning of the list of students (slist) as long as we havn't reached the given id
        pStudent = pStudent->next;
    }
    if (!pStudent) {
        printf("Student not found");
        return;
    }
    student4registration = pStudent->info;    //point at the student's info
    while (pCourse && pCourse->info->number != number) {   //from the beginning of the list of courses (clist) as long as we havn't reached the given course's number
        pCourse = pCourse->next;
    }
    if (!pCourse) {
        printf("Course not found");
        return;
    }
    course2register = pCourse->info;     //point at the course's info

    clist* newCourse = (clist*)malloc(sizeof(clist));
    if (newCourse == NULL) {
        printf("Memory allocation error!\n");
        exit(1);
    }
    newCourse->info = course2register;
    newCourse->next = NULL;
    if (!student4registration->courses) {   //if student hasn't already registered to courses
        student4registration->courses = newCourse;
    }
    else {
        if (student4registration->courses->info->number > number) {
            newCourse->next = student4registration->courses;
            student4registration->courses = newCourse;
        }
        else {
            currentCourse = student4registration->courses;
            while (currentCourse->next && currentCourse->next->info->number < number) {       //we want to point to last node
                currentCourse = currentCourse->next;
            }
            newCourse->next = currentCourse->next;
            currentCourse->next = newCourse;
        }
    }
    slist* newStudent = (slist*)malloc(sizeof(slist));
    if (newStudent== NULL) {
        printf("Memory allocation error!\n");
        exit(1);
    }
        newStudent->info = student4registration;
        newStudent->next = NULL;
        if (!course2register->students) {
            course2register->students = newStudent;
        }
        else {
            if (course2register->students->info->id > id) {
                newStudent->next = course2register->students;
                course2register->students = newStudent;
            }
            else {
                currStudent = course2register->students;
                while (currStudent->next && currStudent->next->info->id < id) {       //we want to point to last node
                    currStudent = currStudent->next;
                }
                newStudent->next = currStudent->next;
                currStudent->next = newStudent;
            }
        }
    }



/*This function will unregister a student from the course*/
void unreg_student(slist * students, int id, int number) {
    student* student2unregister;   //This will point student's info in slist
    course* course2unregisterfrom;   //This will point course's info in clist
    slist* pStudent = students;   //This will point a student's node in slist
    while (pStudent && pStudent->info->id != id) {   //from the beginning of the list of students (slist) as long as we havn't reached the given id
        pStudent = pStudent->next;
    }
    if (pStudent == NULL) {
        printf("Student not found");
        return;
    }
    student2unregister = pStudent->info;   // the student we want to delete from the list of students that registered to the course
    clist* pCourse = student2unregister->courses;   //This will point a course's node in clist
    while (pCourse && pCourse->info->number != number) {  //from the beginning of the courses to which the given student (by id) is registered until we find the course that matches the given number of the course
        pCourse = pCourse->next;
    }
    if (pCourse == NULL) {
        printf("Course not found");
        return;
    }
    course2unregisterfrom = pCourse->info;   //the course we want to delete from the list of courses to which the student is registered
    student2unregister->courses = remove_course(student2unregister->courses, course2unregisterfrom);   //updating the list of courses to which the given student is registered
    course2unregisterfrom->students = remove_student(course2unregisterfrom->students, student2unregister);   //updating the list of students that registered to given course
    }


/*This function remove a course from the list of courses which the student has regisered*/
clist* remove_course(clist* coursesOfStudent, course* courseInfo) {
    clist* pCourse = coursesOfStudent, *course2delete;
    if (coursesOfStudent == NULL) {
        printf("Student not registered in any course ");
        return coursesOfStudent;
    }
    if (pCourse->info->number != courseInfo->number) {    //if the course from which the student want to unregister is not the first on the list
        while (pCourse && pCourse->next->info->number != courseInfo->number) {   //temp will be point the course the before the given course in the list
            pCourse = pCourse->next;
        }
        if (pCourse == NULL) {
            printf("Student was not registered to that course");
            return coursesOfStudent;
        }
        course2delete = pCourse->next;   //the course we want to delete
        pCourse->next = course2delete->next;
        free(course2delete); 
    }
    else {    //if the course from which the student want to unregister is the first on the list
        coursesOfStudent = pCourse->next;
        free(pCourse);
    }
    return coursesOfStudent;   //return the list of courses of the student without the course he wanted to unregister
}


/*This function remove a student from the list of students which has registered to the course*/
    slist* remove_student(slist * students, student * studentInfo) {
        slist* pStudent = students, * student2delete;
        if (pStudent->info == studentInfo) {   //if the student to delete from list of students who registered to given course is the first in the list
            if (!(pStudent->next)) {   //if the student is the only one in the list
                free(pStudent);
                return NULL;    //return an empty list
            }
            student2delete = pStudent->next;   //the first in the list will be the second student so the given student is deleted
            free(pStudent);
            return student2delete;   //return a list without the given student
        }
        while (pStudent->next->info != studentInfo) {   //until we point the course that the next one is the student we want to delete
            pStudent = pStudent->next;
        }
        student2delete = pStudent->next;   //the student we want to delete
        pStudent->next = student2delete->next;   
        free(student2delete);
        return students;
    }


    /* This function prints a list of all the students – for each student it prints ID, name, and a list of
       courses the student is registered for. The order in which the students are printed is by their ID from low
       to high. The order in which the courses that each student is registered for are printed is by their
       number, from low to high. */
    void print_students(slist* students) {
        slist* pCourseOfStudent = students->info->courses;
        while (students) {
            printf("*************************** \n");
            printf("~Name of student~ \n");
            printf("%s \n", students->info->name);
            printf("~ID of student~ \n");
            printf("%d \n", students->info->id);
            printf("~The student is enrolled in the following courses~ \n");
            while (pCourseOfStudent) {
                printf("%s \n", pCourseOfStudent->info->name);
                pCourseOfStudent = pCourseOfStudent->next;
            }
            students = students->next;
            if (students){
                pCourseOfStudent = students->info->courses;
            }
        }
        putchar('\n');
    }


    /*This function prints a list of all the courses – for each course it prints number, title, and a list of
     all students that are registered to that course. The order in which the courses are printed is by their
     number, from low to high. The order in which the student lists are printed is by their ID from low to high.*/
    void print_courses(clist* courses) {
        slist* pStudentsOfCourse = courses->info->students;
        while (courses) {
            printf("*************************** \n");
            printf("~Name of course~ \n");
            printf("%s \n", courses->info->title);
            printf("~Number of course~ \n");
            printf("%d \n", courses->info->number);
            printf("~The students enrolled in this course~ \n");
            while (pStudentsOfCourse) {
                printf("%s \n", pStudentsOfCourse->info->name);
                pStudentsOfCourse = pStudentsOfCourse->next;
            }
            courses = courses->next;
            if (courses) {
                pStudentsOfCourse = courses->info->students;
            }
        }
        putchar('\n');
    }



    /*This function receives the student and course lists and releases all allocated memory. */
    void free_all(slist* sl, clist* cl) {
        slist *currStudent = sl,*pStudent, *pPrevStudent;
        clist  *currCourse = cl, *pCourse, *pPrevCourse;
        student*studentInfo;
        course *courseInfo;
        while (currStudent) {
            studentInfo = currStudent->info;
            free(studentInfo->name);
            pCourse = studentInfo->courses;
            while (pCourse) {
                pPrevCourse = pCourse;
                pCourse = pCourse->next;
                free(pPrevCourse);
            }
            pPrevStudent = currStudent;
            currStudent = currStudent->next;
            free(pPrevStudent);
        }
        while (currCourse) {
            courseInfo = currCourse->info;
            free(courseInfo->title);
            pStudent = courseInfo->students;
            while (pStudent) {
                pPrevStudent = pStudent;
                pStudent = pStudent->next;
                free(pPrevStudent);
            }
            pPrevCourse = currCourse;
            currCourse = currCourse->next;
            free(pPrevCourse);
        }
    }