#include <stdio.h>

int main() {
        int a = 6;
        int b = 2;
        printf("a = %d ", a);
        printf("b = %d \n", b);
        a = a+b;
        b = a-b;
        a = a-b;
        printf("a = %d ", a);
        printf("b = %d \n", b);
}
