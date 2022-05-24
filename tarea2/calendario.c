/*
*
* EJECUCION DEL PROGRAMA  gcc calendario.c -o calendario && ./calendario 
*Julio Barra
*Vania Vergara
*
*Se pide observar y analizar el comportamiento del algortimos al momento de que este tenga sumas más, menos o igual a 24, para la prueba se testeo solo con 2 tareas.
*
*Para menor que 24 se observo que la tabla se lleno en quien tomaba el recurso primero, siendo el uno o el dos ingresando y llenandose sin problema aparente
*
*Luego al ser igual a 24, ocurrio lo mismo que en el anterior, sin sobrepasarse o cambio relevante
*
*Finalmente al ingresar mas horas de las que tiene el dia el programa simplemente ignoro las demas horas en el dia, siendo llenada hasta donde se alcanzaba, para el ejemplo
*se uso 14 horas para la tarea 1 y 12 para la tarea 2, siendo la tarea 2 quien tomo antes el recurso y se lleno los primeros 12 bloques y luego para la tarea uno 
*se lleno la tabla con los espacios que quedaba (12), sobrando 2 horas que quedaron perdidas en el algoritmo.
*
*En conclusion para igual o menor que las horas en un dia el programa no presenta mayor inconveniente, pero para mayor de 24 el programa simplemente ignora
*las otras horas dejandolas "perdidas".
*
*/

//LIBRERIAS
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

//declaramos el calendario globalmente y lo iniciamos en 0
static int scheduler[7][24] = { {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
                            };

//declaramos mutex-lock
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

//creamos objeto de las tareas que hay que realizar
struct tareas {
    int horas, diaLimite, horaLimite, numeroDeTarea;
};

//SCHEDULER de primero que entra primero que sera atendido
void *firstComeFirstServed(void *datoSinVariable)
{
    struct tareas *dato = (struct tareas *) datoSinVariable;

    //iiniciamos el mutex 
    pthread_mutex_lock(&mutex);

    //se meten los datos al scheduler
    for(int i = 0; i < dato->horas; i++)
    {
        for(int j = 0; j < 24; j++)
        {
            if(scheduler[dato->diaLimite][j] == 0)
            {
                scheduler[dato->diaLimite][j] = dato->numeroDeTarea;
                j = 24;
            }
        }
    }

    //imprimimos calendario a medida que los datos van ingresando sl scheduler
    printf("|-----------------------------------------------------------------------------------------------|\n");
    printf("|   Horas   |   Lunes   |   Martes  | Miercoles |   Jueves  |  Viernes  |   Sabado  |  Domingo  |\n");
    printf("|-----------------------------------------------------------------------------------------------|\n");

    for(int i = 0; i < 24; i++)
    {

        if( i < 9)
        {
            printf("|     %d     |", i + 1);
        }
        else
        {
            printf("|     %d    |", i + 1);
        }
        for(int j = 0; j < 7; j++)
        {
            printf("     %d     |", scheduler[j][i]);
        }
        printf("\n");
        printf("|-----------------------------------------------------------------------------------------------|\n");
    }

    pthread_mutex_unlock(&mutex);

    return "todo bn";
}

int main() 
{
    //VARIABLES
    int cantidadTareas, horas, diaLimite, horaLimite;

    printf("Ingrese la cantidad de tareas que tiene para la semana : ");
    scanf("%d", &cantidadTareas);

    pthread_t ingresaDatos[cantidadTareas];

    struct tareas fechaTareas[cantidadTareas];

    //pedimos datos y creamos los hilos
    for(int i = 0; i < cantidadTareas; i++)
    {
        printf("Tarea %d\n", i + 1);
        printf("Ingrese horas a dedicar : ");
        scanf("%d", &horas);
        printf("Ingrese dia limite de la tarea (0-6): ");
        scanf("%d", &diaLimite);
        printf("Ingrese horas limite de la tarea (0-23) : ");
        scanf("%d", &horaLimite);

        fechaTareas[i].horas = horas;
        fechaTareas[i].diaLimite = diaLimite;
        fechaTareas[i].horaLimite = horaLimite;
        fechaTareas[i].numeroDeTarea = i + 1;

    }

    //invocamos a los hilos de manera que el primero que agarre el recurso entre, no necesariamente sera el i = 0
    for(int i = 0; i < cantidadTareas; i++)
    {
        pthread_create(&ingresaDatos[i], NULL, firstComeFirstServed, &fechaTareas[i]);
    }
    
    for(int i = 0; i < cantidadTareas; i++)
    {
        pthread_join(ingresaDatos[i], NULL);
    }

    return 0;
}