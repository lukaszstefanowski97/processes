#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

char **leftHistory;
char **rightHistory;
int range;

void printInputError() {
    printf("This script needs an argument.\nPlease type a string after running .c file.\n");
}

int isPowerOfTwo(int number) {
    if ((number & (number - 1)) == 0) return 1;
    return 0;
}

int getSubstringRange(int stringRange) {
    do --stringRange;
    while (isPowerOfTwo(stringRange) == 0);
    return stringRange;
}

char *getSubstring(const char *string, int range) {
    char *substring = malloc(range * sizeof(char));
    for (int i = 0; i < range; ++i) {
        substring[i] = string[i];
    }
    return substring;
}

char *getRightHalf(const char *string, int size) {
    char *substring = malloc(size / 2 * sizeof(char));
    for (int i = size / 2; i < size; ++i) {
        substring[i - size / 2] = string[i];
    }
    return substring;
}

char *getLeftHalf(const char *string, int size) {
    char *substring = malloc(size / 2 * sizeof(char));
    for (int i = 0; i < size / 2; ++i) {
        substring[i] = string[i];
    }
    return substring;
}

void saveToHistory(char *string, int side) {
    int i = 0;
    if (side == 1) {
        while (i < range) {
            if (rightHistory[i] == "null") {
                rightHistory[i] = string;
                break;
            } else i++;
        }
    } else {
        while (i < range) {
            if (leftHistory[i] == "null") {
                leftHistory[i] = string;
                break;
            } else i++;
        }
    }
}

void cutRight(char *string, int side);

void cutLeft(char *string, int side) {
    if (strlen(string) == 1) {
    } else {
        char *left = getLeftHalf(string, (int) strlen(string));
        saveToHistory(left, side);
        printf("%s\n", left);
        cutLeft(left, side);
        cutRight(left, side);
    }
}

void cutRight(char *string, int side) {
    if (strlen(string) == 1) {
    } else {
        char *right = getRightHalf(string, (int) strlen(string));
        printf("%s\n", right);
        saveToHistory(right, side);
        cutLeft(right, side);
        cutRight(right, side);
    }
}

void initiate(char **array1, char **array2, int size) {
    for (int i = 0; i < size; i++) {
        array1[i] = "null";
        array2[i] = "null";
    }
}

void cutStrings(char *string) {
    printf("Basic string: %s\n", string);
    printf("Length: %d\n", (int) strlen(string));
    leftHistory[0] = string;
    rightHistory[0] = string;
    printf("\nLeft subtree: \n");
    cutLeft(string, 0);
    printf("\nRight subtree: \n");
    cutRight(string, 1);
}

void printString(char *string, int pid) {
    printf("\n%d ", pid);
    fflush(stdout);
    printf("%s ", leftHistory[0]);
    fflush(stdout);
    for (int i = 1; i < range; i++) {
        if (strstr(leftHistory[i], string)) {
            printf("%s ", leftHistory[i]);
            fflush(stdout);
            if (leftHistory[i] == string) break;
        }
        if (strstr(rightHistory[i], string)) {
            printf("%s ", rightHistory[i]);
            fflush(stdout);
            if (rightHistory[i] == string) break;
        }
    }
}

void runProcess(char *string, int isItFirstProcess) {
    pid_t pid = fork();
    if (pid < 0) {
        perror("brzydko\n");
        exit(-1);
    } else if (pid != 0) {
        if (isItFirstProcess == 1) {
            printf("\n%d %s", getpid(), string);
            fflush(stdout);
        }
        wait(NULL);
    } else {
        if (isItFirstProcess == 0) {
            printString(string, getpid());
        }
        execl("/bin/echo", "echo", " ", NULL);
    }
}

void runProcesses(char **left, char **right, int range) {
    runProcess(left[0], 1);
    for (int i = 1; i < range; i++) {
        runProcess(left[i], 0);
        runProcess(right[i], 0);
    }
}

void setUpEnv(int range, char *string) {
    leftHistory = malloc((range) * sizeof(char *));
    rightHistory = malloc((range) * sizeof(char *));
    initiate(leftHistory, rightHistory, range);
    cutStrings(string);
}

int main(int argc, char *argv[]) {
    if (!argv[1]) {
        printInputError();
        return 1;
    } else {
        char *string = argv[1];
        range = (int) strlen(string);
        if (isPowerOfTwo(range) == 0) {
            char *substring = getSubstring(string, getSubstringRange(range));
            setUpEnv(getSubstringRange(range), substring);
            runProcesses(leftHistory, rightHistory, getSubstringRange(range));
            free(substring);
        } else if (range == 1) {
            setUpEnv(range, string);
            runProcess(string, 1);
        } else {
            setUpEnv(range, string);
            runProcesses(leftHistory, rightHistory, range);
        }
        free(leftHistory);
        free(rightHistory);
    }
    return 0;
}
