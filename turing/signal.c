#include <stdio.h>
#include <signal.h>

void jelkezelo(int sig_num) {
        printf("Elkapva %d\n", sig_num);
}

int main() {
  for(;;) {
          if(signal(SIGINT, jelkezelo)==SIG_IGN)
          signal(SIGINT, SIG_IGN);
          }
  return 0;
}
