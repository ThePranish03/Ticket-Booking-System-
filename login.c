#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define TABLE_SIZE 100
#define MAX_NAME_LENGTH 50


char* hashTable[TABLE_SIZE] = {NULL};


int hashFunction(const char* username);
void insertUser(const char* username);
int searchUser(const char* username);

int main() {
    int choice;
    char username[MAX_NAME_LENGTH];

    while (1) {
        printf("\n1. Insert Username\n2. Search Username\n3. Exit\nEnter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter username to insert: ");
                scanf("%s", username);
                insertUser(username);
                break;

            case 2:
                printf("Enter username to search: ");
                scanf("%s", username);
                if (searchUser(username))
                    printf("User '%s' found in hash table.\n", username);
                else
                    printf("User '%s' NOT found.\n", username);
                break;

            case 3:
                printf("Exiting...\n");
                return 0;

            default:
                printf("Invalid choice.\n");
        }
    }

    return 0;
}

int hashFunction(const char* username) {
    int sum = 0;
    for (int i = 0; username[i] != '\0'; i++) {
        sum += username[i];
    }   
    return sum % TABLE_SIZE;
}

void insertUser(const char* username) {
    int index = hashFunction(username);

    for (int i = 0; i < TABLE_SIZE; i++) {
        int try = (index + i) % TABLE_SIZE;

        if (hashTable[try] == NULL) {
            hashTable[try] = (char*)malloc(strlen(username) + 1);
            strcpy(hashTable[try], username);
            printf("User '%s' inserted at index %d\n", username, try);
            return;
        }
    }

    printf("Hash table is full. Cannot insert '%s'\n", username);
}


int searchUser(const char* username) {
    int index = hashFunction(username);

    for (int i = 0; i < TABLE_SIZE; i++) {
        int try = (index + i) % TABLE_SIZE;


        if (hashTable[try] == NULL){
            return 0;
        }
        
        if (strcmp(hashTable[try], username) == 0){
            return 1;
        }
    }

    return 0;
}