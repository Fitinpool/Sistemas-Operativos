#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main(void)
{
    int fd[2];
    pid_t ubicacionActual;
    int cantidadCiudades;
    char encontrado[15] = "";

    printf("Cantidad posiciones para zulensky : ");
    scanf("%d", &cantidadCiudades);

    srand(getpid());

    int ubicacionZulensky = rand() % cantidadCiudades + 1;

    printf("Zulensky se encuentra en %d\n", ubicacionZulensky);

    for(int i = 0; i < cantidadCiudades; i++)
    {
        pipe(fd);
        ubicacionActual = fork();
        switch (ubicacionActual)
        {
            case 0:
                /* Jugador */
                srand(getpid());
                int zulensky = rand() % cantidadCiudades + 1;
                close(fd[0]);

                if(zulensky == ubicacionZulensky)
                {
                    printf("zulensky encontrado en %d \n", getpid());
                    write(fd[1],"encontrado", sizeof("encontrado"));
                    close(fd[1]);
                }
                else
                {
                    printf("Ubicacion %d allanada, sin señales de Zulensky en coordenadas %d \n", zulensky, getpid());
                    write(fd[1],"no encontrado", sizeof("no encontrado"));
                    close(fd[1]);
                }

                exit(0);
                break;
            case -1:
                /* Error */
                break;
            default:
                /* Padre */
                close(fd[1]);
                read(fd[0], encontrado, sizeof(encontrado));

                if(strcmp(encontrado, "encontrado") == 0)
                {
                    return 0;
                }
                else
                {
                    i--;
                }

                close(fd[0]);
        }
    }

    return 0;
}