#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "main.h"

void getUserInput(char* password, int size);
char* getUserString(char* buff, int n);
int calcStrengthScore(char* password, int size);
void printMenu();

int main(int argc, char const *argv[])
{   
    int score = 0;
    printMenu();
    return 0;
}

void printMenu()
{
    printf("Welcome to the password checker!\nPlease enter the password you want to check:\n");
    char passwordBuff[100] = {0};
    char *sPassword;
    
    //get password from user
    int bufSize = sizeof(passwordBuff);
    getUserString(passwordBuff, bufSize);
    sPassword = passwordBuff;
    int passwordSize = strlen(sPassword);
    printf("Password entered: %s\n", sPassword); 

    //check strength of password and print result
    int score = calcStrengthScore(sPassword, passwordSize);
}

char* getUserString(char* buff, int n)
{
 char *userInput = fgets(buff, n-1, stdin);
 userInput[strlen(userInput)-1] = '\0';
 return userInput; 
}

int calcStrengthScore(char* password, int size)
{
    int score = 0;
    printf("Size: %d\n", size);
    
    //character type scoring
    for (int i = 0; i < size; i++)
    {
        char c = password[i];
        printf("char: %c", c);
        printf("Score: %d\n", score);
        if(isupper(c))
        {
            score += 2;
        }
        else if (islower(c))
        {
            score += 1;
        }
        else if (isdigit(c))
        {
            score += 2; 
        }
        else 
        {
            score += 3; 
        }

        //length scoring
        if (size > 8)
        {
            score += 1; 
        }
        if (size > 12)
        {
            score += 1;
        }
         if (size > 17)
        {
            score += 1;
        }
        if (size > 20)
        {
            score += 1;
        }
    }
        /*score classification:
        Very weak = 0-2
        Weak = 3-5
        Medium = 6-8
        Strong = 9-12
        Very Strong = > 12
        */
        if (score == 0 || score <= 2)
        {
            printf("Your password is very weak! Score: %d\n", score);
        }
        else if (score >= 3 && score <= 5)
        {
            printf("Your password is weak! Score: %d\n", score);
        }
        else if (score >= 6 && score <= 8)
        {
            printf("Your password is medium! Score: %d\n", score);
        }
        else if (score >= 9 && score <= 12)
        {
            printf("Your password is strong! Score: %d\nGood job! Could still be better. \n", score);
        }
        else if (score > 12)
        {
            printf("Your password is very strong! Score: %d\nTop score! \n", score);
        }

    return score; 
}