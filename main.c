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

int calculatePathLength(int stringLength) {
    int pathLength = stringLength;
    if (isPowerOfTwo(stringLength) == 1) {
        pathLength = pathLength + 2;
        --stringLength;
    } else if (stringLength == 1) {
        ++pathLength;
        --stringLength;
    } else --stringLength;

    if (stringLength == 0) return pathLength;
}

int getSubstringRange(int stringRange) {
    if (isPowerOfTwo(stringRange) == 1) return stringRange;
    --stringRange;
    getSubstringRange(stringRange);
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

void runRightSubProcess(char * string, int range, char * path, int wasSubProcessRunned);

void runLeftSubProcess(char * string, int range, char * path, int wasSubProcessRunned) {
    if (range == 1 && wasSubProcessRunned == 0) {
    } else if (range == 2) {
        char* leftSubstring = getLeftHalf(string, range);
        strcat(path, leftSubstring);
        strcat(path, " ");
        char* rightSubstring = getRightHalf(string, range);
        strcat(path, rightSubstring);
        printf("%s\n", path);
    } else {
        char* leftSubstring = getLeftHalf(string, range);
        strcat(path, leftSubstring);
        strcat(path, " ");
        runLeftSubProcess(leftSubstring, range/2, path, 1);
        runRightSubProcess(getRightHalf(string, range), range/2, path, 1);
    }
}

void runRightSubProcess(char * string, int range, char * path, int wasSubProcessRunned) {
    if (range == 1 && wasSubProcessRunned == 0) {

    } else if (range == 2) {
        char* leftSubstring = getLeftHalf(string, range);
        strcat(path, leftSubstring);
        strcat(path, " ");
        char* rightSubstring = getRightHalf(string, range);
        strcat(path, rightSubstring);
        printf("%s", path);
    } else {
        char* rightSubstring = getRightHalf(string, range);
        strcat(path, rightSubstring);
        strcat(path, " ");
        runLeftSubProcess(getLeftHalf(string, range), range/2, path, 1);
        runRightSubProcess(rightSubstring, range/2, path, 1);
    }
}

void runProcess(char *string, int range, char *leftPath, char *rightPath) {
    if (range == 1) {
        if (rightPath[strlen(rightPath) - 1] == ' ') {
            strcat(rightPath, string);
            printf("cond: %s\n", rightPath);
            //free(leftPath);
        } else {
            strcat(leftPath, string);
            printf("cond: %s\n", leftPath);
            //free(rightPath);
        }
    } else if (isPowerOfTwo(range) == 1) {
            strcat(leftPath, string);
            strcat(leftPath, " ");
            strcat(rightPath, string);
            strcat(rightPath, " ");
                char* leftSubstring = getLeftHalf(string, range);
                runProcess(leftSubstring, range/2, leftPath, rightPath);
//                runLeftSubProcess(leftSubstring, range, leftPath, 0);
//                runRightSubProcess(leftSubstring, range, leftPath, 0);
                char *rightSubstring = getRightHalf(string, range);
                runProcess(rightSubstring, range/2, leftPath, rightPath);

//                runLeftSubProcess(rightSubstring, range, rightPath, 0);
//                runRightSubProcess(rightSubstring, range, rightPath, 0);

    } else {
        int substringRange = getSubstringRange(range);
        char *substring = getSubstring(string, substringRange);
        runProcess(substring, substringRange, leftPath, rightPath);
        free(substring);
    }
}

int pathLength;
char *leftPath;
char *rightPath;

int main(int argc, char *argv[]) {
//    if (!argv[1]) {
//        printInputError();
//        return 1;
//    } else {
        //char *string = argv[1];
        char *string = "abcdefgh";
//        int range = strlen(argv[1]);
        int range = strlen(string);
        pathLength = calculatePathLength(range);
        leftPath = malloc(pathLength * sizeof(char));
        rightPath = malloc(pathLength * sizeof(char));
        runProcess(string, range, leftPath, rightPath);
//    }
    return 0;
}
