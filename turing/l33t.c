#include <stdio.h>

int main() {
    int i = 0;
    char string[50];

    printf("Enter your string: ");

    fgets(string,50,stdin);

    while (string[i]!='\0') {

        if (string[i]=='a') {

            string[i]='4';

        } else if (string[i]=='i') {
                string[i]='1';
        } else if (string[i]=='e') {
                string[i]='3';
        } else if (string[i]=='t') {
                string[i]='7';
        } else if (string[i]=='o') {
                string[i]='0';
        }
        i++;
    }
    printf("Your string in 1337: %s\n", string);
    return 0;
}
