#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/types.h>
#include <time.h>

int main(int argc, char** argv){
	if (argc < 2){
		perror("Invalid number of arguments");
		exit(1);
	}
	int n;
	n = atoi(argv[1]);
	int p2c[2], c2p[2];
	pipe(p2c);
	pipe(c2p);
	srand(time(0));
	int f = fork();
	if (f == -1){
		perror("Error on fork");
		exit(1);
	}
	else{
		if (f == 0){
			close(p2c[1]);	close(c2p[0]);
			int numar = 0, suma = 0;
			read(p2c[0], &numar, sizeof(int));
			for (int i = 1; i<=numar; ++i){
				int numarCurent = 0;
				read(p2c[0], &numarCurent, sizeof(int));
				suma += numarCurent;
			}
			close(p2c[0]);
			float media = suma / (float) numar;
			write(c2p[1], &media, sizeof(float));
			close(c2p[1]);
			exit(0);
		}
	}
	close(p2c[0]); close(c2p[1]);
	write(p2c[1], &n, sizeof(int));
	for (int i = 1; i<=n;++i){
		int numar = rand() % 100;
		printf("Nr generat: %d\n", numar);
		write(p2c[1], &numar, sizeof(int));
	}
	close(p2c[1]);
	float media = 0;
	read(c2p[0], &media, sizeof(float));
	printf("Media este: %f\n", media);
	close(c2p[0]);
	wait(NULL);
	return 0;
}
