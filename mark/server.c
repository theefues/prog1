#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<pthread.h>

#define PORT 8889
#define MAX 2

struct thread_args {
    int *client;
    struct sockaddr_in *addr;
    int id;
};

int inarray(char *msg, char *arr[]) {
    int i;
    for(i = 0; i < 5; i++)
        if(strcmp(arr[i], msg) == 0)
            return 1;
    return 0;
}

int valid(char msg[], char * to){
    int i = 0;
    for(i = 0; i < strlen(to); i++)
        if(msg[i] != to[i])
            return 1;
    return 0;
}
void *connection_handler(void *);
int sockets[MAX];
int connected = 0;
int elso, masodik;
int kor = 0;
int hajok = 0;
char hajo1[5][5];
char hajo2[5][5];
int ready = 0;
int hajj = 0;
int hajk = 0;
int p1 = 5;
int p2 = 5;


int main(int argc , char *argv[]) {
	int fd, fd_client, c, *new_sock, on = 1, max = MAX, i, id;
	struct sockaddr_in server, client, *new_addr;
	
    for(i = 0; i < max; i++)
        sockets[i] = -1;

	fd = socket(AF_INET , SOCK_STREAM , 0);
	if (fd == -1){
		printf("create fail");
        exit(1);
	}
	
	setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, (char *)on, sizeof on);
    setsockopt(fd, SOL_SOCKET, SO_KEEPALIVE, (char *)on, sizeof on);

	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(PORT);
	
	if( bind(fd,(struct sockaddr *)&server , sizeof(server)) < 0)
	{
		perror("bind fail");
		return 1;
	}

	listen(fd , 99999);

	
	printf("+-------------------------------+\n");
	printf("|  A szerver él PORT: %d      |\n", PORT);
	printf("+-------------------------------+\n\n");
	c = sizeof(struct sockaddr_in);

	while((fd_client = accept(fd, (struct sockaddr *)&client, (socklen_t*)&c)) )
	{
        id = 0;
        while(sockets[id] != -1 && id < max)
            id++;
        if (id >= max) {
            printf(" [x] Kapcsolódás elutasítva: %s:%d\n", inet_ntoa(client.sin_addr), ntohs(client.sin_port));
            close(fd_client);
            continue;
        }

        sockets[id] = fd_client;

		printf(" [+] Kapcsolódás elfogadva: %s:%d\n", inet_ntoa(client.sin_addr), ntohs(client.sin_port));
		
		
        struct thread_args args;
		pthread_t sniffer_thread;
		new_sock = (int*)malloc(sizeof(int));
		*new_sock = fd_client;
        new_addr = (struct sockaddr_in *)malloc(sizeof(struct sockaddr_in));
        *new_addr = client; 

        args.client = new_sock;
        args.addr = new_addr;
        args.id = id;

		if (pthread_create(&sniffer_thread, NULL, connection_handler, (void*)&args) < 0)
		{
			perror("could not create thread");
			return 1;
		}
	}
	
	if (fd_client < 0)
	{
		perror("accept failed");
		return 1;
	}

    close(fd);
	
	return 0;
}

void *connection_handler(void *arguments)
{
    int i, max = MAX, read_size;
    struct thread_args *args = (struct thread_args *) arguments;
	int sock = *(int*)args->client;
    struct sockaddr_in addr = *(args->addr);
	char *message , client_message[1024];
	
	


	message = "[+] Sikeres kapcsolódás!\n"; connected++;
	write(sock, message, strlen(message));

    for(i = 0; i < max; i++) 
        if(sockets[i] > -1){
			if(connected <= 1) {
				elso = sockets[i];
				message = "[...] Várakozás a másik játékosra.\n";
				write(sockets[i], message, strlen(message));
			} else if(connected == 2) {
				masodik = sockets[i];
				message = "[+] Második játékos megérkezett, kezdődik a játék.\n";
				write(sockets[i], message, strlen(message));
			}
        }


kore:
	if(connected == 2 && ready == 0) {
		if(hajok != 10) {
				if(kor%2 == 0) {
					message = ":get";
					write(elso, message, strlen(message));
					message = ":wait";
					write(masodik, message, strlen(message));
					bzero(client_message, sizeof(client_message));
					recv(elso, client_message, 10, 0);
					for(int l = 0; l < 5; l++ ){
						if(strcmp(hajo1[l], client_message) == 0){
							message = ":same";
							write(elso, message, strlen(message));
							bzero(client_message, sizeof(client_message));
							kor = 0;
							goto kore;
						}
					}
					strcpy(hajo1[hajj], client_message);
					hajj++;
				} else { 
					message = ":get";
					write(masodik, message, strlen(message));
					message = ":wait";
					write(elso, message, strlen(message));
					bzero(client_message, sizeof(client_message));
					recv(masodik, client_message, 10, 0);
					for(int f = 0; f < 5; f++ ){
						if(strcmp(hajo2[f], client_message) == 0){
							message = ":same";
							write(masodik, message, strlen(message));
							bzero(client_message, sizeof(client_message));
							kor = 1;
							goto kore;
						}
					}
					strcpy(hajo2[hajk], client_message);
					hajk++;
				} 
		} else {
			ready = 1;
			kor = 0;
			goto kore;
		}
			
	} else if(connected == 2 && ready == 1){
		saw:
		if(kor%2 == 0 && p1 > 0 && p2 > 0) {
					message = ":tip";
					write(elso, message, strlen(message));
					message = ":wait";
					write(masodik, message, strlen(message));
					bzero(client_message, sizeof(client_message));
					recv(elso, client_message, 10, 0);
					for(int l = 0; l < 5; l++ ){
						if(strcmp(hajo2[l], client_message) == 0){
							message = ":hit";
							strcpy(hajo2[l], "");
							write(elso, message, strlen(message));
							p2--;
							printf("P2 Élet: %d maradt\n", p2);
							goto try;
						}
					}
					message = ":miss";
					write(elso, message, strlen(message));
					goto try;
				} else if(kor%2 != 0 && p1 > 0 && p2 > 0) { 
					message = ":tip";
					write(masodik, message, strlen(message));
					message = ":wait";
					write(elso, message, strlen(message));
					bzero(client_message, sizeof(client_message));
					recv(masodik, client_message, 10, 0);
					for(int f = 0; f < 5; f++ ){
						if(strcmp(hajo1[f], client_message) == 0){
							message = ":hit";
							strcpy(hajo1[f], "");
							write(masodik, message, strlen(message));
							p1--;
							printf("P1 Élet: %d maradt\n", p1);
							goto try;
						}
					}
					message = ":miss";
					write(masodik, message, strlen(message));
					goto try;
				} else {
					if(p1 == 0) {
						message = ":win";
						write(masodik, message, strlen(message));
						message = ":lose";
						write(elso, message, strlen(message));
						exit(1);
					} else if (p2 == 0) {
						message = ":win";
						write(elso, message, strlen(message));
						message = ":lose";
						write(masodik, message, strlen(message));
						exit(1);
					}
				}
	}
try:
	while ((read_size = recv(sock, client_message, 10 , 0)) > 0) {
		
		if(valid(client_message, "felad") == 0) {
			printf("%d számú játékos feladta.\n", kor);
			if(kor%2 == 0) {
				message = "[._.] Vesztettél!\n";
	        	write(sockets[0], message, strlen(message));
				message = "[^.^] Nyertél, az ellenfeled feladta!\n";
	        	write(sockets[1], message, strlen(message));
			} else {
				message = "[._.] Vesztettél!\n";
	        	write(sockets[1], message, strlen(message));
				message = "[^.^] Nyertél, az ellenfeled feladta!\n";
	        	write(sockets[0], message, strlen(message));
			}
			exit(1);
		} else {
			printf("[>] Fogadva[%d]: %s\n", sock, client_message);
		}
		bzero(client_message, sizeof(client_message));
		kor++;
		hajok++;
		if(ready == 0) {
			goto kore;
		} else {
			goto saw;
		}
		
	}
	
	
	if (read_size == 0) {
        printf("[-] Kapcsolódás vége: %s:%d\n", inet_ntoa(addr.sin_addr), ntohs(addr.sin_port));
		connected--;
        sockets[args->id] = -1;
	} else if(read_size == -1) {
		perror("recv failed");
	}
	return 0;
}
