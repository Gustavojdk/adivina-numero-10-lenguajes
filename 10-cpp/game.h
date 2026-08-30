#ifndef GAME_H
#define GAME_H

#include <random>
#include <string>

// Mantiene la lógica y el estado de una partida (sin depender de Qt).
class Game
{
public:
    static constexpr int NumeroMinimo = 1;
    static constexpr int NumeroMaximo = 100;

    Game();

    std::string comprobarNumero(int numero);
    void reiniciar();
    int obtenerIntentos() const;
    bool estaFinalizado() const;

private:
    std::mt19937 generador;
    int numeroSecreto;
    int intentos;
    bool finalizado;
};

#endif
