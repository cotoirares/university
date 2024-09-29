#include "header.h"

int main(int argc, char** argv){
	mkfifo(myfifo1, 0600);
	mkfifo(myfifo2, 0600);
	int fd_write = open(myfifo1, O_WRONLY);
	int fd_read = open(myfifo2, O_RDONLY);
	srand(getpid());
	while (1){
		int nr = rand() % 10 + 1;
		write(fd_write, &nr, sizeof(int));
		int nr_citit = 0;
		read(fd_read, &nr_citit, sizeof(int));
		printf("Am trimis numarul %d si am primit numarul %d\n", nr, nr_citit);
		if (nr_citit == 10 || nr == 10)
			break;
	}
	unlink(myfifo1);
	unlink(myfifo2);
	return 0;
}
