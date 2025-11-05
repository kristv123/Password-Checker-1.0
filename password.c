// password.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "password.h"

int calcStrengthScore(char *password, int size);
void getFeedback(char *password, int size);
int isCommonPassword(char *password);

int calcStrengthScore(char *password, int size)
{
    int score = 0;
    // printf("Size: %d\n", size);

    if (isCommonPassword(password))
    {
        printf("Your password is found in the list of common passwords.\n");
        return 0; // score of 0 for common passwords
    }

    // character type scoring
    for (int i = 0; i < size; i++)
    {
        char c = password[i];
        // printf("char: %c", c);
        // printf("Score: %d\n", score);
        if (isupper(c))
        {
            score += 1;
        }
        else if (islower(c))
        {
            score += 0;
        }
        else if (isdigit(c))
        {
            score += 1;
        }
        else
        {
            score += 3;
        }
    }

    // length scoring
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

    /*score classification:
    Very weak = 0-2
    Weak = 3-5
    Medium = 6-8
    Strong = 9-12
    Very Strong = > 12
    */

    const char *color;
    if (score == 0 || score <= 2)
    {
        color = "\033[1;31m"; // Red
        printf("Your password is very weak!\n");
    }
    else if (score >= 3 && score <= 5)
    {
        color = "\033[1;91m"; // Light red
        printf("Your password is weak!\n");
    }
    else if (score >= 6 && score <= 8)
    {
        color = "\033[1;33m"; // Yellow
        printf("Your password is medium!\n");
    }
    else if (score >= 9 && score <= 12)
    {
        color = "\033[1;92m"; // Light green
        printf("Your password is strong!\nGood job! Could still be better. \n");
    }
    else if (score > 12)
    {
        color = "\033[1;32m"; // Green
        printf("Your password is very strong!\nTop score! \n");
    }

    return score;
}

int isCommonPassword(char *password)
{
    FILE *file = fopen("Pwdb_top-1000.txt", "r");
    if (file == NULL)
    {
        perror("Could not open common_passwords.txt");
        return -1; // Indicate error
    }
    char line[100];
    while (fgets(line, sizeof(line), file))
    {
        line[strcspn(line, "\n")] = 0; // Remove newline character
        // Compare with the input password
        if (strcmp(line, password) == 0)
        {
            fclose(file);
            return 1; // Password is common
        }
    }
    return 0; // Password is not common
}

void getFeedback(char *password, int size)
{
    printf("Improvements:\n");
    if (size < 8)
    {
        printf("- Password is too short. Consider using at least 8 characters.\n");
    }
    else if (size < 12)
    {
        printf("- Consider using more than 12 characters for even better security.\n");
    }
    if (!strpbrk(password, "ABCDEFGHIJKLMNOPQRSTUVWXYZ"))
    {
        printf("- Add uppercase letters to increase complexity.\n");
    }
    if (!strpbrk(password, "!\"#$%%&'()*+,-./:;<=>?@[\\]^_`{|}~"))
    {
        printf("- Include special characters to enhance strength.\n");
    }
    if (!strpbrk(password, "0123456789"))
    {
        printf("- Incorporate numbers to make your password stronger.\n");
    }
    if (isCommonPassword(password) == 1) // TODO: Fix double call to isCommonPassword
    {
        printf("- Avoid using common passwords found in password lists.\n");
    }
    printf("\n");
}
