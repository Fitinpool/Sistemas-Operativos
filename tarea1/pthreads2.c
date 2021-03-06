/*
  Compilar:
    gcc -o pthreads2 pthreads2.c -lpthread
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int max;
volatile int counter = 0; // Variable compartida global

void *mythread(void *arg)
{
    char *letter = arg;
    int i; // stack (privado por thread) 
    printf("%s: inicio [direccion de i: %p]\n", letter, &i);
    for (i = 0; i < max; i++) 
    {
    	//printf("%s: sumando\n", letter);
		counter = counter + 1; // compartido: solo uno
    }
    printf("%s: terminado\n", letter);
    return NULL;
}
                                                                             
int main(int argc, char *argv[])
{                    
    if (argc != 2) 
    {
		fprintf(stderr, "uso: ./pthreads2 <n_ciclos>\n");
		exit(1);
    }
    max = atoi(argv[1]);

    pthread_t p1, p2;
    printf("main: inicio [contador = %d] [%lx]\n", counter, (unsigned long) &counter);
    pthread_create(&p1, NULL, mythread, "A"); 
    pthread_create(&p2, NULL, mythread, "B");
    // join esperan a que los threads terminen
    pthread_join(p1, NULL); 
    pthread_join(p2, NULL); 
    printf("main: terminado\n [contador: %d]\n [esperado: %d]\n", counter, max*2);
    return 0;
}

