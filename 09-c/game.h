#ifndef GAME_H
#define GAME_H

#include <stdbool.h>

#define NUMERO_MINIMO 1
#define NUMERO_MAXIMO 100

// Mantiene la lógica y el estado de una partida.
typedef struct {
    int numero_secreto;
    int intentos;
    bool finalizado;
} Juego;

void iniciar_juego(Juego *juego);
void reiniciar_juego(Juego *juego);
const char *comprobar_numero(Juego *juego, int numero);

#endif
