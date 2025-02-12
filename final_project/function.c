#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "datatype.h"
#include "function.h"
#define MAX_USERS 100
#define DATA_FILE "user.bin"

int userExists(const char *userId);
User users[MAX_USERS];
int userCount = 0;

void saveUsersToFile() {
    FILE *file = fopen("user.bin", "wb");
    if (file) {
        fwrite(&userCount, sizeof(int), 1, file);
        fwrite(users, sizeof(User), userCount, file);
        fclose(file);
    }
}

void loadUsersFromFile() {
    FILE *file = fopen("user.bin", "rb");
    if (file) {
        fread(&userCount, sizeof(int), 1, file);
        fread(users, sizeof(User), userCount, file);
        fclose(file);
    } else {
        userCount = 0;
    }
}
void displayRoleMenu() {
    int roleChoice;
    do {
          printf("\n***Bank Management System Using C***\n");
        printf("\n%9sCHOOSE YOUR ROLE\n","");
        printf("%5s========================\n");
        printf("%5s[1] Admin.\n");
        printf("%5s[2] User.\n");
        printf("%5s[0] Exit the Program.\n");
        printf("%5s========================\n");
        printf("%5sEnter The Choice: ");
        scanf("%d", &roleChoice);
        while (getchar() != '\n');
    } while (roleChoice < 1 || roleChoice > 2);
    int choice;
    do {
     printf("\n***Student Management System Using C***\n");
        printf("\n%15sMENU\n","");
        printf("%8s========================\n");
        printf("%8s[1] Add A New user.\n");
        printf("%8s[2] Show All users.\n");
        printf("%8s[3] Show detail an user.\n");
        printf("%8s[4] Lock (Unlock) an user.\n");
        printf("%8s[5] User Guideline.\n");
        printf("%8s[6] About Us.\n");
        printf("%8s[0] Exit the Program.\n");
        printf("%8s========================\n");
        printf("%8sEnter The Choice: ");
        scanf("%d", &choice);
        while (getchar() != '\n');
        
        switch (choice) {
            case 1:
                addUser();
                break;
            case 2:
                displayUsers();
                break;
            case 3:
                showUserDetail();
                break;
            case 4:
                toggleUserStatus();
                break;
            case 5:
                userGuideline();
                break;
            case 6:
                aboutUs();
                break;
            case 0:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid option! Try again.\n");
        }
    } while (choice != 0);
}

void displayUsers() {
    char choice;
    do {
        printf("\n========================================================================================\n");
        printf("| %-10s | %-20s | %-20s | %-15s | %-10s |\n", "ID", "Name", "Email", "Phone", "Status");
        printf("========================================================================================\n");
        for (int i = 0; i < userCount; i++) {
            printf("| %-10s | %-20s | %-20s | %-15s | %-10s |\n", 
                users[i].userId, users[i].name, users[i].email, users[i].phone, users[i].status ? "Lock" : "Open");
        }
        printf("========================================================================================\n");

        // Keep prompting until 'b' or '0' is entered
        printf("Go back(b)? or Exit(0)?: ");
        scanf(" %c", &choice);
        while (getchar() != '\n'); // Clear input buffer

        if (choice == '0') {
            exit(0);
        }
    } while (choice != 'b');
}
int userExists(const char *userId) {
    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].userId, userId) == 0) {
            return 1;
        }
    }
    return 0;
}

void addUser() {
    if (userCount >= MAX_USERS) {
        printf("User list is full!\n");
        return;
    }

    User newUser;
    printf("Enter ID: ");
    fgets(newUser.userId, sizeof(newUser.userId), stdin);
    newUser.userId[strcspn(newUser.userId, "\n")] = '\0'; // Remove newline

    if (userExists(newUser.userId)) {
        printf("User ID already exists!\n");
        return;
    }

    printf("Enter Name: ");
    fflush(stdin);
    fgets(newUser.name, sizeof(newUser.name), stdin);
    newUser.name[strcspn(newUser.name, "\n")] = '\0'; // Remove newline

    printf("Enter Phone: ");
     fflush(stdin);
    fgets(newUser.phone, sizeof(newUser.phone), stdin);
    newUser.phone[strcspn(newUser.phone, "\n")] = '\0'; // Remove newline

    printf("Enter Email: ");
     fflush(stdin);
    fgets(newUser.email, sizeof(newUser.email), stdin);
    newUser.email[strcspn(newUser.email, "\n")] = '\0'; // Remove newline

    printf("Enter Date of Birth (DD MM YYYY): ");
     fflush(stdin);
    scanf("%d %d %d", &newUser.dateOfBirth.day, &newUser.dateOfBirth.month, &newUser.dateOfBirth.year);
    while (getchar() != '\n'); 

    users[userCount++] = newUser;
    saveUsersToFile();
    printf("User added successfully!\n");
}



void toggleUserStatus() {
    char userId[10];
    printf("Enter User ID to lock/unlock: ");
    fgets(userId, sizeof(userId), stdin);
    userId[strcspn(userId, "\n")] = 0;

    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].userId, userId) == 0) {
            users[i].isLocked = !users[i].isLocked;
            printf("User %s is now %s\n", users[i].name, users[i].isLocked ? "Locked" : "Unlocked");
            saveUsersToFile();
            return;
        }
    }
    printf("User ID not found!\n");
}
void userGuideline() {
    printf("\nUser Guideline:\n");
    printf("1. Use option 1 to add a new user.\n");
    printf("2. Use option 2 to view all users.\n");
    printf("3. Use option 3 to view a specific user’s details.\n");
    printf("4. Use option 4 to lock/unlock users.\n");
    printf("5. Follow on-screen instructions for seamless navigation.\n");
}
void aboutUs() {
    printf("\nAbout Us:\n");
    printf("This is a simple user management system developed in C.\n");
    printf("It allows user registration, viewing details, and managing access.\n");
}
void showUserDetail() {
    char userId[10];
    printf("Enter User ID to view details: ");
    fgets(userId, sizeof(userId), stdin);
    strtok(userId, "\n");
    
    int found = 0;
    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].userId, userId) == 0) {
            found = 1;
            printf("\nUser Details:\n");
            printf("ID: %s\n", users[i].userId);
            printf("Name: %s\n", users[i].name);
            printf("Date of Birth: %02d/%02d/%04d\n", users[i].dateOfBirth.day, users[i].dateOfBirth.month, users[i].dateOfBirth.year);
            printf("Phone: %s\n", users[i].phone);
            printf("Email: %s\n", users[i].email);
            break;
        }
    }
    
    if (!found) {
        printf("User ID not found!\n");
    }
}
