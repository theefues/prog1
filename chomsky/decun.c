#include <stdio.h>

int main() {
        int szam;
        printf("Adj meg egy számot: ");
        if (scanf("%d", &szam)) {
                for(int i = 0; i < szam; i++){
                        if(i % 5 == 0 && i != 0)
                        printf(" ");

                        printf("|");
                }
                printf("\n");
        } else {
                printf("Kérlek, számot adj meg.\n");
        }
}
