#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

volatile int num_jugadores = 2;

int main(void)
{
    int jugadorArbitro[2], arbitroJugador[2];
    pid_t jugando;
    char eleccion1[10] = "";
    char eleccion2[10] = "";
    char desicion[12] = "";
    int num;
    char *jugada[] = {"tijeras", "papel", "roca"};
    int jugadaTPR;

    char lol[] = "lol";

    for(int i = 0; i < num_jugadores; i++)
    {
        pipe(jugadorArbitro);

        jugando = fork();
        
        switch (jugando)
        {
            case 0:
                /* Jugador */

                close(jugadorArbitro[0]);

                srand(getpid());

                jugadaTPR = (rand() % 3);

                write(jugadorArbitro[1], jugada[jugadaTPR], sizeof(jugada[jugadaTPR]));
                close(jugadorArbitro[1]);

                printf("Jugador %d: %s\n", getpid(), jugada[jugadaTPR]);

                exit(0);
                break;
            case -1:
                /* Error */
                break;
            default:
                /* Padre */
                close(jugadorArbitro[1]);
                read(jugadorArbitro[0], eleccion2, sizeof(eleccion2));
                
                if(strcmp(eleccion1, "") == 0)
                {
                    strcpy(eleccion1, eleccion2);
                }
                else
                {
                    printf(" 1: %s || 2: %s\n", eleccion1, eleccion2);

                    if(strcmp(eleccion1,"tijeras") == 0 && strcmp(eleccion2,"papel") == 0)
                    {
                        printf("Jugador 1 gana\n");
                    }
                    else if(strcmp(eleccion1,"tijeras") == 0 && strcmp(eleccion2,"roca") == 0)
                    {
                        printf("Jugador 2 gana\n");
                    }
                    else if(strcmp(eleccion1,"roca") == 0 && strcmp(eleccion2,"papel") == 0)
                    {
                        printf("Jugador 2 gana\n");
                    }
                    else if(strcmp(eleccion1,"roca") == 0 && strcmp(eleccion2,"tijeras") == 0)
                    {
                        printf("Jugador 1 gana\n");
                    }
                    else if(strcmp(eleccion1,"papel") == 0 && strcmp(eleccion2,"roca") == 0)
                    {
                        printf("Jugador 1 gana\n");
                    }
                    else if(strcmp(eleccion1,"papel") == 0 && strcmp(eleccion2,"tijeras") == 0)
                    {
                        printf("Jugador 2 gana\n");
                    }
                    else if(strcmp(eleccion1,eleccion2) == 0)
                    {
                        strcpy(desicion, "perdiste");
                        printf("Empate\n");
                    }

                    strcpy(eleccion1, "");
                    strcpy(eleccion2, "");
                }

                break;
        }
    }

    return 0;
}