#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Student {
    int id;
    char name[50];
    int age;
    char course[50];
};

void addStudent();
void displayStudents();
void searchStudent();
void updateStudent();
void deleteStudent();

int main() {
    int choice;

    while (1) {
        printf("\n===== STUDENT MANAGEMENT SYSTEM =====\n");
        printf("1. Add Student\n");
        printf("2. Display Students\n");
        printf("3. Search Student\n");
        printf("4. Update Student\n");
        printf("5. Delete Student\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                addStudent();
                break;

            case 2:
                displayStudents();
                break;

            case 3:
                searchStudent();
                break;

            case 4:
                updateStudent();
                break;

            case 5:
                deleteStudent();
                break;

            case 6:
                printf("Exiting...\n");
                exit(0);

            default:
                printf("Invalid choice!\n");
        }
    }

    return 0;
}

void addStudent() {
    FILE *fp;
    struct Student s;

    fp = fopen("students.dat", "ab");

    if (fp == NULL) {
        printf("File cannot be opened!\n");
        return;
    }

    printf("\nEnter Student ID: ");
    scanf("%d", &s.id);

    printf("Enter Name: ");
    scanf(" %[^\n]", s.name);

    printf("Enter Age: ");
    scanf("%d", &s.age);

    printf("Enter Course: ");
    scanf(" %[^\n]", s.course);

    fwrite(&s, sizeof(s), 1, fp);

    fclose(fp);

    printf("Student added successfully!\n");
}

void displayStudents() {
    FILE *fp;
    struct Student s;

    fp = fopen("students.dat", "rb");

    if (fp == NULL) {
        printf("No records found!\n");
        return;
    }

    printf("\n===== STUDENT RECORDS =====\n");

    while (fread(&s, sizeof(s), 1, fp)) {
        printf("\nID      : %d", s.id);
        printf("\nName    : %s", s.name);
        printf("\nAge     : %d", s.age);
        printf("\nCourse  : %s\n", s.course);
    }

    fclose(fp);
}

void searchStudent() {
    FILE *fp;
    struct Student s;
    int id, found = 0;

    fp = fopen("students.dat", "rb");

    if (fp == NULL) {
        printf("File not found!\n");
        return;
    }

    printf("Enter Student ID to search: ");
    scanf("%d", &id);

    while (fread(&s, sizeof(s), 1, fp)) {
        if (s.id == id) {
            printf("\nStudent Found!\n");
            printf("ID      : %d\n", s.id);
            printf("Name    : %s\n", s.name);
            printf("Age     : %d\n", s.age);
            printf("Course  : %s\n", s.course);

            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Student not found!\n");
    }

    fclose(fp);
}

void updateStudent() {
    FILE *fp;
    struct Student s;
    int id, found = 0;

    fp = fopen("students.dat", "rb+");

    if (fp == NULL) {
        printf("File not found!\n");
        return;
    }

    printf("Enter Student ID to update: ");
    scanf("%d", &id);

    while (fread(&s, sizeof(s), 1, fp)) {
        if (s.id == id) {

            printf("Enter New Name: ");
            scanf(" %[^\n]", s.name);

            printf("Enter New Age: ");
            scanf("%d", &s.age);

            printf("Enter New Course: ");
            scanf(" %[^\n]", s.course);

            fseek(fp, -sizeof(s), SEEK_CUR);
            fwrite(&s, sizeof(s), 1, fp);

            printf("Student updated successfully!\n");

            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Student not found!\n");
    }

    fclose(fp);
}

void deleteStudent() {
    FILE *fp, *temp;
    struct Student s;
    int id, found = 0;

    fp = fopen("students.dat", "rb");

    if (fp == NULL) {
        printf("File not found!\n");
        return;
    }

    temp = fopen("temp.dat", "wb");

    printf("Enter Student ID to delete: ");
    scanf("%d", &id);

    while (fread(&s, sizeof(s), 1, fp)) {
        if (s.id == id) {
            found = 1;
        } else {
            fwrite(&s, sizeof(s), 1, temp);
        }
    }

    fclose(fp);
    fclose(temp);

    remove("students.dat");
    rename("temp.dat", "students.dat");

    if (found) {
        printf("Student deleted successfully!\n");
    } else {
        printf("Student not found!\n");
    }
}
