#include "header1.h"


int main(int argc, char** argv){
	mkfifo(myfifo3, 0600);
	mkfifo(myfifo4, 0600);
	int fd_write = open(myfifo3, O_WRONLY);
	int fd_read = open(myfifo4, O_RDONLY);
	int n;
	while(1){
		scanf("%d", &n);
		write(fd_write, &n, sizeof(int));
		int numar_divizori = 0;
		read(fd_read, &numar_divizori, sizeof(int));
		if (numar_divizori == 0){
			printf("Numar prim, programul se opreste.");
			break;
		}
		else{
			printf("Numarul are %d divizori si acestia sunt: \n", numar_divizori);
			for (int i = 1; i<=numar_divizori; i++){
				int div = 0;
				read(fd_read, &div, sizeof(int));
				printf("%d, ", div);
			}
			printf("\n");
		}
	}
	unlink(myfifo3);
	unlink(myfifo4);
	return 0;
}
