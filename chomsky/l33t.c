#include <stdio.h>

int main(int argc, char **argv) {
    if(argc < 2) {
            printf("error: no input file, changing to manual input\n");
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
                            string[i] = '0';
                            break;
                    case 'S':
                    case 's':
                            string[i] = '5';
                            break;
                    default:
                            break;
                }
                i++;
            }
            printf("Your string in 1337: %s", string);
            fclose(stri);
            return 0;
    } else {
            int i = 0;
            int k = 14400;
            FILE *stri = fopen(argv[1], "r");
            char string[k];
            fgets(string, k, stri);
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
                            string[i] = '0';
                            break;
                    case 'S':
                    case 's':
                            string[i] = '5';
                            break;
                    default:
                            break;
                }
                i++;
            }
            printf("Your string in 1337: %s", string);
            fclose(stri);
            return 0;
            }
}
