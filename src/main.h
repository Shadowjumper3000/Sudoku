#ifndef MAIN_H
#define MAIN_H

// Include any libraries here
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>


// Declare any global variables here
#define DEBUG 0

// Declare function prototypes here
int printField();
int acceptInput();
int solveField();
int copyField();

int determineOS() {
    #ifdef _WIN32
        return 0;
    #elif _WIN64
        return 0;
    #elif __APPLE__ || __MACH__
        return 1;
    #elif __linux__
        return 2;
    #elif __unix__
        return 3;
    #else
        return 4;
    #endif
}

int clearScreen() {
    int os = determineOS();
    if (os == 0) {
        system("cls");
    } else if (os == 1) {
        system("clear");
    } else if (os == 2) {
        system("clear");
    } else if (os == 3) {
        system("clear");
    } else {
        printf("Unknown OS\n");
    }
    return 0;
}

#endif