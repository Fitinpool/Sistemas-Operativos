#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*Variables Globales*/

int rc=0;

struct escritor{
	int libroID;
};

struct lector{
	int libroLeido;
};

struct libro{
	int cantLectores;
	int ID;
	FILE * libro;
};

int num_lectores;

FILE *archivo;

/*Semaforos*/

sem_t mutex,db;

/*Funciones*/

void *lector(void *p);
void *escritor(void *p);
void escribirenbasedatos();
void leerenbasedatos();

int main(int argc, char *argv[]){

	int estado,i;

	printf("Ingrese numero de alumnos: ");
	scanf("%d", &num_lectores);

	struct escritor Escitores[2];

	Escitores[0].libroID = 0;
	Escitores[1].libroID = 1;

	struct libro Libros[2];

	Libros[0].ID = 0;
	Libros[0].cantLectores = num_lectores;
	Libros[0].libro = fopen("libro1.txt", "w");
	fclose(Libros[0].libro);
	Libros[1].ID = 1;
	Libros[1].cantLectores = num_lectores;
	Libros[1].libro = fopen("libro2.txt", "w");
	fclose(Libros[0].libro);

	
	struct lector Lectores[num_lectores];
	
	for(int i = 0; i < num_lectores; i++)
	{
		Lectores[i].libroLeido = -1;
	}

	/*Declaración de las dos hebras*/

	pthread_t escritora[2],lectora[num_lectores];

	printf("todo bn");
	
	sem_init(&mutex,0,1);
	sem_init(&db,0,1);

	for(int i = 0; i < 2; i++)
	{
		pthread_create(&escritora[i], NULL, escritor, &Escitores[i]);
	}
	
	/*
	for(i=0;i<num_lectores;i++){
		lectoresID[i]=i;
		if((estado=pthread_create(&lectora[i],NULL,lector,(void *) &lectoresID[i])))
			exit(estado);
	}

	for(i=0;i<num_escritores;i++){
		escritoresID[i]=i;
		if((estado=pthread_create(&escritora[i],NULL,escritor,(void *) &escritoresID[i])))
			exit(estado);
	}

	for(i=0;i<num_lectores;i++)
	{
		pthread_join(lectora[i],NULL);
	}
	for(i=0;i<num_escritores;i++)
	{
		pthread_join(escritora[i],NULL);
	}*/

	sem_destroy(&mutex);
	sem_destroy(&db);	
	return 0;
}

/*
void escribirenbasedatos(){

	extern FILE *baseDatos;
	char c;
	baseDatos=fopen("baseDatos.txt","a+");

	while ((c=getc(stdin))!=EOF){
		fputc(c,baseDatos);
	}
	fclose(baseDatos);	

}
void leerenbasedatos(){
	
	extern FILE *baseDatos;
	Datos p;        
	baseDatos=fopen("baseDatos.txt","r");

	while (fscanf(baseDatos,"%s\n%s\n%d\n",p.nombre,p.apellido,&p.edad)==3){

		printf("\nNombre:");
		puts(p.nombre);
		printf("Apellidos:");
		puts(p.apellido);
		printf("Edad:\n");
		printf("%d",p.edad);
	}

	fclose(baseDatos);

}*/


void *escritor(void *p){

		extern sem_t mutex,db;
		char caracter;
		struct escritor *dato = (struct escritor *) p;
		
		sem_wait(&db);

			printf("soy lecto %d leyendo", dato->libroID);
			extern FILE *archivo;
			archivo = fopen("prueba.txt","r");

			char *contents = NULL;
			size_t len = 0;
			while (getline(&contents, &len, archivo) != -1){
				printf("%s", contents);
			}

			fclose(archivo);
			free(contents);
		sem_post(&db);
		

		pthread_exit(NULL);

}
/*
void *lector(void *p){

		extern sem_t mutex,db;
		extern int rc;
		int *id_le;

        	id_le=(int *)p;
		
		sem_wait(&mutex);
		rc++;
		if(rc == 1)
		   sem_wait(&db);

		
		printf("\nLector %d Leyendo...\n",*id_le);
		leerenbasedatos();
		sem_post(&mutex);
		sem_wait(&mutex);
		rc--;

		if(rc == 0)
		  sem_post(&db);

		sem_post(&mutex);
		pthread_exit(NULL);
}*/