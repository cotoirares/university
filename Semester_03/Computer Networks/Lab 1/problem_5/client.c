#include <sys/types.h>

#include <sys/socket.h>

#include <stdio.h>

#include <netinet/in.h>

#include <netinet/ip.h>

#include <string.h>

#include <unistd.h>

#include <arpa/inet.h>

 

int main() {

       int c;

       struct sockaddr_in server;

       uint16_t a, number_of_divisors;
       int divizor[32];
       c = socket(AF_INET, SOCK_STREAM, 0);

       if (c < 0) {

              printf("Eroare la crearea socketului client\n");
              return 1;

       }

       memset(&server, 0, sizeof(server));
       server.sin_port = htons(1234);
       server.sin_family = AF_INET;
       server.sin_addr.s_addr = inet_addr("127.0.0.1");
       if (connect(c, (struct sockaddr *) &server, sizeof(server)) < 0) {
              printf("Eroare la conectarea la server\n");
              return 1;
       }

 

       printf("a = ");

       scanf("%hu", &a);

       a = htons(a);

       send(c, &a, sizeof(a), 0);
       recv(c, &suma, sizeof(number_of_divisors), 0);i
       for (int i = 1; i<=number_of_divisors; ++i){
	      recv(c, divizor+i, sizeof(divizor[i]), 0);
	      divizor[i] = ntohl(divizor[i]);
       }	
       suma = ntohs(suma);
      
       close(c);
}
