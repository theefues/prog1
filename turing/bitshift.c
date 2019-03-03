#include <stdio.h>

int main() {
  int i = 1;
  int b = 0;
    while (i != 0) {
      i <<= 1;
      b++;
    }
  printf("Szóhossz: %d bit\n",b);
}
