// main.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "main.h"
int calcStrengthScore(char *password, int size);
void getUserInput(char *password, int size);
char *getUserString(char *buff, int n);
void printMenu();
void printColorBar(int score, const char *color);
char *getColor(int score);
void getFeedback(char *password, int size);

int main(int argc, char const *argv[])
{
    int score = 0;
    printMenu();
    return 0;
}

// prints the main menu and handles user interaction
void printMenu()
{
    printf("Welcome to the password checker!\nPlease enter the password you want to check:\n> ");
    char passwordBuff[100] = {0};
    char *sPassword;

    // get password from user
    int bufSize = sizeof(passwordBuff);
    getUserString(passwordBuff, bufSize);
    sPassword = passwordBuff;
    int passwordSize = strlen(sPassword);
    printf("Password entered: %s\n", sPassword);

    // check strength of password and print result
    int score = calcStrengthScore(sPassword, passwordSize);
    printColorBar(score, getColor(score));
    getFeedback(sPassword, passwordSize);
}

// gets user input and stores it in the provided buffer
char *getUserString(char *buff, int n)
{
    char *userInput = fgets(buff, n - 1, stdin);
    userInput[strlen(userInput) - 1] = '\0';
    return userInput;
}

char *getColor(int score)
{
    const char *color;
    if (score == 0 || score <= 2)
    {
        color = "\033[1;31m"; // Red
    }
    else if (score >= 3 && score <= 5)
    {
        color = "\033[1;91m"; // Light red
    }
    else if (score >= 6 && score <= 8)
    {
        color = "\033[1;33m"; // Yellow
    }
    else if (score >= 9 && score <= 12)
    {
        color = "\033[1;92m"; // Light green
    }
    else if (score > 12)
    {
        color = "\033[1;32m"; // Green
    }
    return (char *)color;
}

// prints a color bar representing the strength score
void printColorBar(int score, const char *color)
{
    printf("\nStrength %d:\n", score);
    printf("%s[", color);
    for (int i = 0; i < 12; i++)
    {
        if (i < score)
            printf("█");
        else
            printf("░");
    }
    printf("]\n%s", "\033[0m\n"); // Reset color
}