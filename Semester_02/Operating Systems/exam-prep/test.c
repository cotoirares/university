#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>


int main(int argc, char** argv){
	int n;
	scanf("%d", &n);
	for (int i=1;i<=n;++i){
		int f = fork();
		if (f == -1){
			perror("error on fork");
			exit(1);
		}
		if (f == 0){
			printf("PID: %d, Parent PID: %d\n",getpid(), getppid());
			exit(0);
		}		
		printf("Parent PID: %d, Child PID: %d\n", getpid(), f);
		wait(NULL);
	}
	return 0;
}
