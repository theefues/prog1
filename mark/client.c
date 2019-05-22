#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <string.h>
#include <regex.h>


#define PORT 8889
 
int match(const char *string, const char *pattern)
{
    regex_t re;
    if (regcomp(&re, pattern, REG_EXTENDED|REG_NOSUB) != 0) return 0;
    int status = regexec(&re, string, 0, NULL, 0);
    regfree(&re);
    if (status != 0) return 0;
    return 1;
}



int valid(char msg[], char * to){
    int i = 0;
    for(i = 0; i < strlen(to); i++)
        if(msg[i] != to[i])
            return 1;
    return 0;
}

int main(int argc , char *argv[]){
    struct winsize ws;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws);

    const char* pattern = "^[0-9]?[0-9]\:[0-9]?[0-9]$";
    int life = 4;
    int on = 1;
    int err;

    char buffer[1024];
    bzero(buffer, sizeof(buffer));

    struct sockaddr_in server;

    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd < 0) {
        printf("Hiba a letrehozaskor!\n");
        exit(1);
    }

    setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, (char *)on, sizeof on);
    setsockopt(fd, SOL_SOCKET, SO_KEEPALIVE, (char *)on, sizeof on);
    
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_port = htons(PORT);

    err = connect(fd, (struct sockaddr *)&server, sizeof server);
    if (err < 0)  error("Nem lehet megnyitni a socketet.");

    while(1){
    //bzero(buffer, sizeof(buffer));
       recv(fd, buffer, 1024, 0);
        if (buffer[0] == '\0') break;
        
        if (valid(buffer, ":get") == 0) {
            re:
            printf("\033[0;33m[^] X,Y koordináta x:y formában: \033[0;33m");
            scanf("%s", &buffer[0]);
            if(!match(buffer, pattern) && !valid(buffer, "felad") == 0){
                printf("\033[0;31m[!] X:Y formátumban add meg!\033[0;31m\n");
                bzero(buffer, sizeof(buffer));
                goto re;
            }
            if(valid(buffer, "felad") == 0) {
                send(fd, buffer, strlen(buffer), 0);
                printf("[._.] Feladtad a játékot!\n");
            } else if(valid(buffer, ":same") == 0) {
                printf("[!] Már van ilyen koordináta!\n");
                bzero(buffer, sizeof(buffer));
                goto re;
            } else {
	            send(fd, buffer, 5, 0);
            }
	    

            if (send(fd, buffer, 5, 0) < 0) {
                error("[x] Nem sikerült kuldes!");
                goto re;
            }
        } else if(valid(buffer, ":wait") == 0) {
            printf("[<] A másik játékos következik.\n");
        } else if(valid(buffer, ":same") == 0) {
                printf("[!] Már van ilyen koordináta!\n");
                bzero(buffer, sizeof(buffer));
                goto re;
        } else if(valid(buffer, ":win") == 0) {
                printf("\033[1;31m[!] Nyertél!\033[1;31m[^]\n");
                bzero(buffer, sizeof(buffer));
                exit(1);

        } else if(valid(buffer, ":lose") == 0) {
                printf("\033[0;31m[!] Vesztettél!\n\033[0;31m[^]");
                bzero(buffer, sizeof(buffer));
                exit(1);

        } else if(valid(buffer, ":miss") == 0) {
                printf("[!] Nem talált!\n");
        
         } else if(valid(buffer, ":hit") == 0) {
                printf("[!] Talált!\n");

        } else if(valid(buffer, ":tip") == 0) {
            tip:
            printf("\033[0;33m[^] Tippeld meg az X,Y koordinátát x:y formában: \033[0;33m");
            scanf("%s", &buffer[0]);
            if(!match(buffer, pattern) && !valid(buffer, "felad") == 0){
                printf("\033[0;31m[!] X:Y formátumban add meg!\033[0;31m\n");
                bzero(buffer, sizeof(buffer));
                goto tip;
            }
            if(valid(buffer, "felad") == 0) {
                send(fd, buffer, strlen(buffer), 0);
                printf("[._.] Feladtad a játékot!\n");
            } else if(valid(buffer, ":same") == 0) {
                printf("[!] Már van ilyen koordináta!\n");
                bzero(buffer, sizeof(buffer));
                goto re;
            } else {
	            send(fd, buffer, 5, 0);
            }
	    

            if (send(fd, buffer, 5, 0) < 0) {
                error("[x] Nem sikerült kuldes!");
                goto re;
            }
        
        } else {
            printf("%s\n", buffer);
        }


        bzero(buffer, sizeof(buffer));
    }
    printf("[-] Kilépés...\n");

    close(fd);

    return 0;
}
