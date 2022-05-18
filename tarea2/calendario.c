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
    int horas, diaLimite, horaLimite;
};

int main() 
{
    int cantidadTareas;

    int horas, diaLimite, horaLimite;

    printf('Ingrese la cantidad de tareas que tiene para la semana : ');
    scanf('%d', cantidadTareas);

    struct tareas fechaTareas[cantidadTareas];

    for(int i = 0; i < cantidadTareas; i++)
    {
        printf('Ingrese horas a dedicar : ');
        scanf('%d', horas);
        printf('Ingrese dia limite de la tarea : ');
        scanf('%d', diaLimite);
        printf('Ingrese horas limite de la tarea : ');
        scanf('%d', horaLimite);

        fechaTareas[i].horas = horas;
        fechaTareas[i].diaLimite = diaLimite;
        fechaTareas[i].horaLimite = horaLimite;
    }

    pthread_t pideDatos, ingresaDatos;
    


}