#include <stdio.h>

int main() {
        int szam;
        printf("Adj meg egy számot: ");
        if (scanf("%d", &szam)) {
                for(int i = 0; i < szam; i++)
                        printf("|");

                printf("\n");
        } else {
                printf("Kérlek, számot adj meg.\n");
        }
}
