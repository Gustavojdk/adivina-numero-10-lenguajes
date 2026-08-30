#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QWidget>

#include "game.h"

class QLabel;
class QLineEdit;
class QPushButton;

// Ventana del juego: construye la interfaz, valida la entrada y muestra el resultado.
class GameWindow : public QWidget
{
    Q_OBJECT

public:
    explicit GameWindow(QWidget *parent = nullptr);

private:
    void configurarVentana();
    void configurarEventos();
    void procesarIntento();
    bool validarEntrada(int &numero);
    void actualizarIntentos();
    void finalizarJuego();
    void reiniciarJuego();

    Game juego;

    QLineEdit *entrada;
    QPushButton *botonAdivinar;
    QPushButton *botonReiniciar;
    QLabel *mensaje;
    QLabel *contador;
};

#endif
