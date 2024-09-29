#include "header1.h"

int main(int argc, char** argv){
	int fd_read = open(myfifo3, O_RDONLY);
	int fd_write = open(myfifo4, O_WRONLY);	
	int n = 0;
	while(1){
		read(fd_read, &n, sizeof(int));
		int numar_divizori = 0, divizori[100], indice = 1;
		for (int d = 2; d < n; d++)
			if (n % d == 0){
				numar_divizori++;
				divizori[indice++] = d;
			}
		write(fd_write, &numar_divizori, sizeof(int));
		for (int i = 1; i < indice; ++i)
			write(fd_write, &divizori[i], sizeof(int));
	}
	return 0;
}
