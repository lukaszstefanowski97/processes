#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void printInputError() {
    printf("This script needs an argument.\nPlease type a string after running .c file.\n");
}

int isPowerOfTwo(int number) {
    if ((number & (number - 1)) == 0) return 1;
    return 0;
}

int getSubstringRange(int stringRange) {
    do {
        --stringRange;
    } while (isPowerOfTwo(stringRange) == 0);
    return stringRange;
}

char *getSubstring(char *string, int range) {
    char *substring = malloc(range * sizeof(char));
    for (int i = 0; i < range; ++i) {
        substring[i] = string[i];
    }
    return substring;
}

char *getRightHalf(char *string, int size) {
    char *substring = malloc(size / 2 * sizeof(char));
    for (int i = size / 2; i < size; ++i) {
        substring[i - size / 2] = string[i];
    }
    return substring;
}

char *getLeftHalf(char *string, int size) {
    char *substring = malloc(size / 2 * sizeof(char));
    for (int i = 0; i < size / 2; ++i) {
        substring[i] = string[i];
    }
    return substring;
}

void createRightProcesses(char* string) ;

void createLeftProcesses(char *string) {
    if (strlen(string) == 1) {
    }
    else {
        char *left = getLeftHalf(string, strlen(string));
        printf("%s\n", left);
        createLeftProcesses(left);
        createRightProcesses(left);
    }
}

void createRightProcesses(char* string) {
    if (strlen(string) == 1) {
    }
    else {
        char *right = getRightHalf(string, strlen(string));
        printf("%s\n", right);
        createLeftProcesses(right);
        createRightProcesses(right);
    }
}

void createProcesses(char*string) {
    createLeftProcesses(string);
    createRightProcesses(string);
}

int main(int argc, char *argv[]) {
//    if (!argv[1]) {
//        printInputError();
//        return 1;
//    } else {
        //char *string = argv[1];
        char *string = "abcdefghi";
//        int range = strlen(argv[1]);
        int range = (int) strlen(string);
        if (isPowerOfTwo(range) == 0) {
            char * substring = getSubstring(string, getSubstringRange(range));
            printf("%s", substring);
            createProcesses(substring);
        } else createProcesses(string);

    return 0;
}
