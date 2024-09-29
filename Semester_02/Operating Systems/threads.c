#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

int shared_var = 0;
pthread_mutex_t mutex;
pthread_barrier_t barrier;

void* routine(void* arg){
	int m = *((int*)arg);
	int frecv_A[21] = {0};
	int frecv_B[4] = {0};
	for (int i = 1; i<m; ++i){
		int A = rand()%20 + 1;
		int B = rand()%3 + 1;
		pthread_mutex_lock(&mutex);
		shared_var += (A*B);
		printf("New value of the shared var: %d\n", shared_var);
		pthread_mutex_unlock(&mutex);
		frecv_A[A]++;
		frecv_B[B]++;
		pthread_barrier_wait(&barrier);
	}
	
	printf("Freq vector for A:\n");
	for (int i = 1; i<=20;i++)
		printf("%d ", frecv_A[i]);
	printf("\n");
	printf("Freq vector for B:\n");
	for (int i = 1; i<=3;++i)
		printf("%d ", frecv_B[i]);
	printf("\n");
	
	return NULL;		
}

int main(int argc, char** argv){
	srand(time(NULL));
	int n, m;
	if (argc != 3){
		perror("Invalid arguments");
		exit(1);
	}
	n = atoi(argv[1]);
	m = atoi(argv[2]);
	pthread_t th[n+1];
	pthread_mutex_init(&mutex, NULL);
	pthread_barrier_init(&barrier, NULL, n);
	
	for (int i = 0; i<n;++i)
		pthread_create(&th[i], NULL, routine, &m);

	for (int i = 0; i<n;++i)
		pthread_join(th[i], NULL);

	pthread_barrier_destroy(&barrier);
	pthread_mutex_destroy(&mutex);
	return 0;
	
}
