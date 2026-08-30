#include "game.h"

Game::Game()
    : generador(std::random_device{}())
{
    reiniciar();
}

// Empieza una partida nueva con otro número secreto.
void Game::reiniciar()
{
    std::uniform_int_distribution<int> rango(NumeroMinimo, NumeroMaximo);

    numeroSecreto = rango(generador);
    intentos = 0;
    finalizado = false;
}

// Recibe un número ya validado y devuelve el mensaje del intento.
std::string Game::comprobarNumero(int numero)
{
    intentos++;

    if (numero < numeroSecreto) {
        return "Muy bajo";
    }

    if (numero > numeroSecreto) {
        return "Muy alto";
    }

    finalizado = true;
    return "¡Correcto!";
}

int Game::obtenerIntentos() const
{
    return intentos;
}

bool Game::estaFinalizado() const
{
    return finalizado;
}
