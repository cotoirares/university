#include "header.h"

int main(int argc, char** argv){
	int fd_read = open(myfifo1, O_RDONLY);
	int fd_write = open(myfifo2, O_WRONLY);
	srand(getpid());
	while (1){
		int nr = rand() % 10 + 1;
		int nr_citit = 0;
		read(fd_read, &nr_citit, sizeof(int));
		write(fd_write, &nr, sizeof(int));
		printf("Am primit numarul %d si am trimis numarul %d\n", nr_citit, nr);
		if (nr == 10 || nr_citit == 10)
			break;
	}
	return 0;
}
