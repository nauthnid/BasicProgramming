#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTS 1000

struct student {
    char studentID[10];
    char birthdate[20];
    float algebra;
    float calculus;
    float basicProgramming;
    float gpa;
    char fullname[100];
};

struct student students[MAX_STUDENTS];
int num_students = 0;

void enter_students_info() {
    int num;
    printf("Enter number of students (max 1000): ");
    scanf("%d", &num);
    getchar();

    if (num > MAX_STUDENTS) {
        printf("Error: maximum number of students exceeded.\n");
        return;
    }

    for (int i = 0; i < num; i++) {
        struct student new_student;
        printf("Enter information for student %d:\n", i + 1);

        printf("Student ID: ");
        fgets(new_student.studentID, sizeof(new_student.studentID), stdin);
        new_student.studentID[strcspn(new_student.studentID, "\r\n")] = 0;

        printf("Full name: ");
        fgets(new_student.fullname, sizeof(new_student.fullname), stdin);
        new_student.fullname[strcspn(new_student.fullname, "\r\n")] = 0;

        printf("Birth date: ");
        fgets(new_student.birthdate, sizeof(new_student.birthdate), stdin);
        new_student.birthdate[strcspn(new_student.birthdate, "\r\n")] = 0;

        printf("Algebra grade: ");
        scanf("%f", &new_student.algebra);
        getchar(); 

        printf("Calculus grade: ");
        scanf("%f", &new_student.calculus);
        getchar();

        printf("Basic Programming grade: ");
        scanf("%f", &new_student.basicProgramming);
        getchar();

        new_student.gpa = (new_student.algebra + new_student.calculus + new_student.basicProgramming) / 3.0;
        students[num_students++] = new_student;
        printf("Student added successfully!\n");
    }
}

void wait_enter() {
    printf("\nPress ENTER to continue");
    getchar();
    fflush(stdin);
}

void print_students(const struct student *rows, int num_rows, FILE *file) {
    int max_fname_length = 15;

    for (int i = 0; i < num_rows; i++) {
        int fname_length = strlen(rows[i].fullname);
        if (fname_length > max_fname_length) {
            max_fname_length = fname_length;
        }
    }

    char header_format[100];
    sprintf(header_format, "%%-12s%%-%ds%%-15s%%-10s%%-10s%%-10s%%-10s\n", max_fname_length + 2);
    char row_format[100];
    sprintf(row_format, "%%-12s%%-%ds%%-15s%%-10.2f%%-10.2f%%-10.2f%%-10.2f\n", max_fname_length + 2);

    fprintf(file, header_format, "ID", "Full Name", "Birthdate", "Algebra", "Calculus", "BP", "GPA");

    for (int i = 0; i < num_rows; i++) {
        fprintf(file, row_format, rows[i].studentID, rows[i].fullname, rows[i].birthdate,
                rows[i].algebra, rows[i].calculus, rows[i].basicProgramming, rows[i].gpa);
    }
}

void print_students_to_file() {
    FILE *fp = fopen("student_list.txt", "w");
    if (fp == NULL) {
        perror("Error opening file");
        return;
    }
    print_students(students, num_students, fp);
    fclose(fp);
}

void highest_gpa() {
    float max_gpa = -1;
    for (int i = 0; i < num_students; i++) {
        if (students[i].gpa > max_gpa) {
            max_gpa = students[i].gpa;
        }
    }

    struct student table[MAX_STUDENTS];
    int table_current = 0;

    for (int i = 0; i < num_students; i++) {
        if (students[i].gpa == max_gpa) {
            table[table_current++] = students[i];
        }
    }

    print_students(table, table_current, stdout);
}

void lowest_gpa() {
    float min_gpa = 100;
    for (int i = 0; i < num_students; i++) {
        if (students[i].gpa < min_gpa) {
            min_gpa = students[i].gpa;
        }
    }

    struct student table[MAX_STUDENTS];
    int table_current = 0;

    for (int i = 0; i < num_students; i++) {
        if (students[i].gpa == min_gpa) {
            table[table_current++] = students[i];
        }
    }

    print_students(table, table_current, stdout);
}

void highest_BP_grade() {
    float max_bp = -1;
    for (int i = 0; i < num_students; i++) {
        if (students[i].basicProgramming > max_bp) {
            max_bp = students[i].basicProgramming;
        }
    }

    struct student table[MAX_STUDENTS];
    int table_current = 0;

    for (int i = 0; i < num_students; i++) {
        if (students[i].basicProgramming == max_bp) {
            table[table_current++] = students[i];
        }
    }

    print_students(table, table_current, stdout);
}

void search_student() {
    char ID[10];
    printf("Enter student ID: ");
    scanf("%9s", ID);
    fflush(stdin);

    for (int i = 0; i < num_students; i++) {
        if (strcmp(ID, students[i].studentID) == 0) {
            print_students(&students[i], 1, stdout);
            return;
        }
    }
    printf("Student not found.\n");
}

void sort_students() {
    for (int i = 0; i < num_students - 1; i++) {
        for (int j = i + 1; j < num_students; j++) {
            if (students[j].gpa > students[i].gpa) {
                struct student temp = students[i];
                students[i] = students[j];
                students[j] = temp;
            }
        }
    }

    printf("Sorted students by GPA in descending order:\n");
    print_students(students, num_students, stdout);
}

void process_grade() {
    int process_grade_choice;
    while (1) {
        printf("=====================================================================================\n");
        printf("================================== PROCESS GRADES ===================================\n");
        printf("=====================================================================================\n");
        printf("1. Student with highest GPA\n");
        printf("2. Student with lowest GPA\n");
        printf("3. Student with highest Basic Programming grade\n");
        printf("0. Exit\n");
        printf("=====================================================================================\n");
        printf("=====================================================================================\n");
        printf("Enter your choice: ");
        scanf("%d", &process_grade_choice);
        fflush(stdin);
        switch (process_grade_choice) {
        case 1:
            highest_gpa();
            wait_enter();
            break;
        case 2:
            lowest_gpa();
            wait_enter();
            break;
        case 3:
            highest_BP_grade();
            wait_enter();
            break;
        case 0:
            printf("Exiting process grades mode.\n");
            return;
        default:
            printf("Invalid choice!\n");
        }
    }
}

int main() {
    int choice;

    while (1) {
        printf("=====================================================================================\n");
        printf("============================ STUDENT MANAGEMENT SYSTEM ==============================\n");
        printf("=====================================================================================\n");
        printf("1. Enter Student's information\n");
        printf("2. Print student list as a table\n");
        printf("3. Save to text file\n");
        printf("4. Process grades\n");
        printf("5. Search student by ID\n");
        printf("6. Sort the student list by GPA in descending order\n");
        printf("0. Exit\n");
        printf("=====================================================================================\n");
        printf("=====================================================================================\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        fflush(stdin);
        switch (choice) {
        case 1:
            enter_students_info();
            break;
        case 2:
            print_students(students, num_students, stdout);
            wait_enter();
            break;
        case 3:
            print_students_to_file();
            wait_enter();
            break;
        case 4:
            process_grade();
            break;
        case 5:
            search_student();
            wait_enter();
            break;
        case 6:
            sort_students();
            wait_enter();
            break;
        case 0:
            exit(0);
        default:
            printf("Invalid choice!\n");
        }
    }
    return 0;
}
