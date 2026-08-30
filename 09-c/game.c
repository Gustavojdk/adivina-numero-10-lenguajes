#include "game.h"

#include <stdlib.h>
#include <time.h>

void iniciar_juego(Juego *juego)
{
    static bool semilla_inicializada = false;

    if (!semilla_inicializada) {
        srand((unsigned int)time(NULL));
        semilla_inicializada = true;
    }

    reiniciar_juego(juego);
}

void reiniciar_juego(Juego *juego)
{
    juego->numero_secreto = rand() % (NUMERO_MAXIMO - NUMERO_MINIMO + 1)
                           + NUMERO_MINIMO;
    juego->intentos = 0;
    juego->finalizado = false;
}

const char *comprobar_numero(Juego *juego, int numero)
{
    if (juego->finalizado || numero < NUMERO_MINIMO || numero > NUMERO_MAXIMO) {
        return NULL;
    }

    juego->intentos++;

    if (numero < juego->numero_secreto) {
        return "Muy bajo";
    }

    if (numero > juego->numero_secreto) {
        return "Muy alto";
    }

    juego->finalizado = true;
    return "¡Correcto!";
}
