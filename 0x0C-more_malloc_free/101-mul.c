#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/**
 * _isdigit - checks if a string is composed of only digits
 * @s: string to check
 *
 * Return: 1 if the string is composed only of digits, 0 otherwise
 */
void multiply(char *num1, char *num2, char *result) {
    int len1 = strlen(num1);
    int len2 = strlen(num2);
    int i, j, k, carry;
    int *tmp = (int*)calloc(len1+len2, sizeof(int));

    for (i = len1 - 1; i >= 0; i--) {
        carry = 0;
        for (j = len2 - 1; j >= 0; j--) {
            k = i + j + 1;
            tmp[k] += (num1[i] - '0') * (num2[j] - '0') + carry;
            carry = tmp[k] / 10;
            tmp[k] %= 10;
        }
        tmp[i + j + 1] = carry;
    }

    k = 0;
    for (i = 0; i < len1 + len2; i++) {
        if (tmp[i] != 0) {
            k = i;
            break;
        }
    }

    for (i = k, j = 0; i < len1 + len2; i++, j++) {
        result[j] = tmp[i] + '0';
    }
    result[j] = '\0';

    free(tmp);
}

/**
 * main - multiplies two positive numbers
 * @argc: number of arguments
 * @argv: array of arguments
 *
 * Return: 0 on success, 1 on failure
 */
int main(int argc, char **argv) {
    char *num1, *num2, *result;
    int i;

    if (argc != 3) {
        printf("Error\n");
        return 98;
    }

    num1 = argv[1];
    num2 = argv[2];

    for (i = 0; i < strlen(num1); i++) {
        if (!isdigit(num1[i])) {
            printf("Error\n");
            return 98;
        }
    }

    for (i = 0; i < strlen(num2); i++) {
        if (!isdigit(num2[i])) {
            printf("Error\n");
            return 98;
        }
    }

    result = (char*)calloc(strlen(num1)+strlen(num2)+1, sizeof(char));
    multiply(num1, num2, result);
    printf("%s\n", result);
    free(result);

    return 0;
}