#include <stdio.h>

int main() {
    int i = 0;
    char string[50];

    printf("Enter your string: ");

    fgets(string, 50, stdin);

    while (string[i] != '\0') {

        switch (string[i]) {

        case 'A':
        case 'a':
                string[i] = '4';
                break;
        case 'I':
        case 'i':
                string[i] = '1';
                break;
        case 'E':
        case 'e':
                string[i] = '3';
                break;
        case 'T':
        case 't':
                string[i] = '7';
                break;
        case 'O':
        case 'o':
                string[i]=  '0';
                break;
        default:
                break;
        }
        i++;
    }
    printf("Your string in 1337: %s", string);
    return 0;
}
