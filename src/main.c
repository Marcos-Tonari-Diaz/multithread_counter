#include <stdio.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

pthread_mutex_t trava;
int n_primes=0;
int j=0;
unsigned long long int numbers[20];
int i=0; 

int is_prime(unsigned long long int in){
	if (in<2)
		return 0;
	unsigned int d;
	for (d=2; d < in; d++){
		if (in%d == 0)
			return 0;
	}
	return 1;
}

//funcao da thread
void* worker(void *arg){
	int* temp = (int*) arg;
	int t_id = *temp;
	//ciclos da thread
	int k = 0;
	while((t_id+4*k)<=j){
    		pthread_mutex_lock(&trava);
		if (is_prime(numbers[t_id+4*k])) n_primes++;
    		pthread_mutex_unlock(&trava);
		//printf("thread %d, k %d, num %Lu\n", t_id, k, numbers[t_id+4*k]);
		k++;
	}
	return NULL;
}

int main() {

	pthread_t workers[4];

	//entrada
	char in = getchar();
	char buffer[256];
	while (in!='\n'){
		if (in!=' '){
			buffer[i]=in;
			i++;
		}
		else{
			buffer[i]='\0';
			numbers[j] = strtoull(buffer, NULL, 10);
			i=0;
			j++;
		}
		in = getchar();
		if (in=='\n'){
			buffer[i]='\0';
			numbers[j] = strtoull(buffer, NULL, 10);
		}
	} 
	
	//criando as worker threads	
	int ids[4];
	for (i=0; i<4; i++){
		ids[i]=i;
	}

	for (i=0; i<4; i++){
		pthread_create(&(workers[i]), NULL, worker, (void*) &ids[i]);
	}

	//esperando as threads
	for (int i=0; i<4; i++){
		pthread_join(workers[i], NULL);
	}

	printf("%d\n", n_primes);
	return 0;
}
