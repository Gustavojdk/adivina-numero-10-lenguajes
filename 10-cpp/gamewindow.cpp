#include "gamewindow.h"

#include <QFont>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QRegularExpression>
#include <QVBoxLayout>

GameWindow::GameWindow(QWidget *parent)
    : QWidget(parent)
{
    configurarVentana();
    configurarEventos();
}

// Crea los widgets y los coloca en una columna.
void GameWindow::configurarVentana()
{
    QLabel *titulo = new QLabel("Adivina el Número", this);
    QFont fuenteTitulo = titulo->font();
    fuenteTitulo.setPointSize(16);
    fuenteTitulo.setBold(true);
    titulo->setFont(fuenteTitulo);

    QLabel *instruccion = new QLabel("Adivina un número del 1 al 100", this);

    entrada = new QLineEdit(this);
    entrada->setPlaceholderText("Tu número");

    botonAdivinar = new QPushButton("Adivinar", this);
    botonReiniciar = new QPushButton("Reiniciar", this);

    mensaje = new QLabel(this);
    contador = new QLabel(this);

    QVBoxLayout *columna = new QVBoxLayout(this);
    columna->addWidget(titulo);
    columna->addWidget(instruccion);
    columna->addWidget(entrada);
    columna->addWidget(botonAdivinar);
    columna->addWidget(mensaje);
    columna->addWidget(contador);
    columna->addWidget(botonReiniciar);

    setWindowTitle("Adivina el Número");
    resize(320, 260);

    actualizarIntentos();
}

// Conecta los botones y la tecla Enter del campo de texto.
void GameWindow::configurarEventos()
{
    connect(botonAdivinar, &QPushButton::clicked, this, &GameWindow::procesarIntento);
    connect(entrada, &QLineEdit::returnPressed, this, &GameWindow::procesarIntento);
    connect(botonReiniciar, &QPushButton::clicked, this, &GameWindow::reiniciarJuego);
}

void GameWindow::procesarIntento()
{
    int numero = 0;

    if (!validarEntrada(numero)) {
        return;
    }

    mensaje->setText(QString::fromStdString(juego.comprobarNumero(numero)));
    actualizarIntentos();
    entrada->clear();

    if (juego.estaFinalizado()) {
        finalizarJuego();
    }
}

// Acepta solo dígitos y comprueba que el valor esté entre 1 y 100.
bool GameWindow::validarEntrada(int &numero)
{
    const QString texto = entrada->text().trimmed();

    if (texto.isEmpty()) {
        mensaje->setText("Ingresa un número.");
        return false;
    }

    static const QRegularExpression soloNumeros("^[+-]?[0-9]+$");
    if (!soloNumeros.match(texto).hasMatch()) {
        mensaje->setText("Ingresa solamente números.");
        return false;
    }

    // toLongLong falla si el texto no cabe en el tipo de dato.
    bool convertido = false;
    const qlonglong valor = texto.toLongLong(&convertido);

    if (!convertido || valor < Game::NumeroMinimo || valor > Game::NumeroMaximo) {
        mensaje->setText("El número debe estar entre 1 y 100.");
        return false;
    }

    numero = static_cast<int>(valor);
    return true;
}

void GameWindow::actualizarIntentos()
{
    contador->setText(QString("Intentos: %1").arg(juego.obtenerIntentos()));
}

// Tras acertar no se aceptan más intentos hasta reiniciar.
void GameWindow::finalizarJuego()
{
    entrada->setEnabled(false);
    botonAdivinar->setEnabled(false);
}

// Reinicia la partida y deja la interfaz lista para jugar otra vez.
void GameWindow::reiniciarJuego()
{
    juego.reiniciar();

    entrada->clear();
    entrada->setEnabled(true);
    botonAdivinar->setEnabled(true);
    mensaje->clear();
    actualizarIntentos();
    entrada->setFocus();
}
