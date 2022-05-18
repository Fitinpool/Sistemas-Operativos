#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

//declaramos el calendario globalmente
static int scheduler[7][24];

//creamos objeto de las tareas que hay que realizar
struct tareas {
    int horas, diaLimite, horaLimite, deadline;
};

int main() 
{
    int cantidadTareas;

    int horas, diaLimite, horaLimite;

    printf("Ingrese la cantidad de tareas que tiene para la semana : ");
    scanf("%d", &cantidadTareas);

    struct tareas fechaTareas[cantidadTareas];

    for(int i = 0; i < cantidadTareas; i++)
    {
        printf("Tarea %d\n", i + 1);
        printf("Ingrese horas a dedicar : ");
        scanf("%d", &horas);
        printf("Ingrese dia limite de la tarea : ");
        scanf("%d", &diaLimite);
        printf("Ingrese horas limite de la tarea : ");
        scanf("%d", &horaLimite);

        fechaTareas[i].horas = horas;
        fechaTareas[i].diaLimite = diaLimite;
        fechaTareas[i].horaLimite = horaLimite;
        fechaTareas[i].deadline = diaLimite * 24 + horaLimite;

    }

    for(int i = 0; i < cantidadTareas; i++)
    {
        printf("Para tarea %d tenemos %d horas para el %d a las %d.\n", i + 1, fechaTareas[i].horas,fechaTareas[i].diaLimite, fechaTareas[i].horaLimite);
    }


    //pthread_t pideDatos, ingresaDatos;
    


}