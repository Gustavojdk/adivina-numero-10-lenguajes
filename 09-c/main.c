#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#include <gtk/gtk.h>

#include "game.h"

typedef struct {
    Juego juego;
    GtkWidget *entrada;
    GtkWidget *boton_adivinar;
    GtkWidget *mensaje;
    GtkWidget *contador;
} InterfazJuego;

typedef enum {
    ENTRADA_VALIDA,
    ENTRADA_VACIA,
    ENTRADA_NO_NUMERICA,
    ENTRADA_FUERA_DE_RANGO
} EstadoEntrada;

static EstadoEntrada validar_entrada(const char *texto, int *numero);
static void mostrar_error_validacion(InterfazJuego *interfaz, EstadoEntrada estado);
static void actualizar_contador(InterfazJuego *interfaz);
static void finalizar_juego(InterfazJuego *interfaz);
static void procesar_intento(GtkWidget *widget, gpointer datos);
static void reiniciar_partida(GtkWidget *widget, gpointer datos);

int main(int argc, char *argv[])
{
    InterfazJuego interfaz = {0};
    GtkWidget *ventana;
    GtkWidget *contenido;
    GtkWidget *titulo;
    GtkWidget *instrucciones;
    GtkWidget *boton_reiniciar;

    gtk_init(&argc, &argv);
    iniciar_juego(&interfaz.juego);

    ventana = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(ventana), "Adivina el Número");
    gtk_window_set_default_size(GTK_WINDOW(ventana), 380, 320);
    gtk_window_set_position(GTK_WINDOW(ventana), GTK_WIN_POS_CENTER);

    contenido = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_container_set_border_width(GTK_CONTAINER(contenido), 24);
    gtk_container_add(GTK_CONTAINER(ventana), contenido);

    titulo = gtk_label_new(NULL);
    gtk_label_set_markup(
        GTK_LABEL(titulo),
        "<span size=\"x-large\" weight=\"bold\">Adivina el Número</span>"
    );
    instrucciones = gtk_label_new("Adivina un número del 1 al 100");

    interfaz.entrada = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(interfaz.entrada), "Número del 1 al 100");
    gtk_entry_set_alignment(GTK_ENTRY(interfaz.entrada), 0.5F);

    interfaz.boton_adivinar = gtk_button_new_with_label("Adivinar");
    interfaz.mensaje = gtk_label_new("");
    interfaz.contador = gtk_label_new("Intentos: 0");
    boton_reiniciar = gtk_button_new_with_label("Reiniciar");

    gtk_box_pack_start(GTK_BOX(contenido), titulo, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(contenido), instrucciones, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(contenido), interfaz.entrada, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(contenido), interfaz.boton_adivinar, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(contenido), interfaz.mensaje, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(contenido), interfaz.contador, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(contenido), boton_reiniciar, FALSE, FALSE, 0);

    g_signal_connect(ventana, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    g_signal_connect(
        interfaz.boton_adivinar,
        "clicked",
        G_CALLBACK(procesar_intento),
        &interfaz
    );
    g_signal_connect(
        interfaz.entrada,
        "activate",
        G_CALLBACK(procesar_intento),
        &interfaz
    );
    g_signal_connect(
        boton_reiniciar,
        "clicked",
        G_CALLBACK(reiniciar_partida),
        &interfaz
    );

    gtk_widget_show_all(ventana);
    gtk_widget_grab_focus(interfaz.entrada);
    gtk_main();

    return 0;
}

// Valida el texto completo antes de convertirlo a int.
static EstadoEntrada validar_entrada(const char *texto, int *numero)
{
    char *fin;
    long valor;

    while (g_ascii_isspace(*texto)) {
        texto++;
    }

    if (*texto == '\0') {
        return ENTRADA_VACIA;
    }

    errno = 0;
    valor = strtol(texto, &fin, 10);

    if (fin == texto) {
        return ENTRADA_NO_NUMERICA;
    }

    while (g_ascii_isspace(*fin)) {
        fin++;
    }

    if (*fin != '\0') {
        return ENTRADA_NO_NUMERICA;
    }

    if (errno == ERANGE || valor < NUMERO_MINIMO || valor > NUMERO_MAXIMO) {
        return ENTRADA_FUERA_DE_RANGO;
    }

    *numero = (int)valor;
    return ENTRADA_VALIDA;
}

static void mostrar_error_validacion(InterfazJuego *interfaz, EstadoEntrada estado)
{
    const char *mensaje;

    switch (estado) {
    case ENTRADA_VACIA:
        mensaje = "Ingresa un número.";
        break;
    case ENTRADA_NO_NUMERICA:
        mensaje = "Ingresa solamente números.";
        break;
    case ENTRADA_FUERA_DE_RANGO:
        mensaje = "El número debe estar entre 1 y 100.";
        break;
    default:
        return;
    }

    gtk_label_set_text(GTK_LABEL(interfaz->mensaje), mensaje);
}

static void actualizar_contador(InterfazJuego *interfaz)
{
    char texto[32];

    snprintf(texto, sizeof(texto), "Intentos: %d", interfaz->juego.intentos);
    gtk_label_set_text(GTK_LABEL(interfaz->contador), texto);
}

static void finalizar_juego(InterfazJuego *interfaz)
{
    gtk_widget_set_sensitive(interfaz->entrada, FALSE);
    gtk_widget_set_sensitive(interfaz->boton_adivinar, FALSE);
}

static void procesar_intento(GtkWidget *widget, gpointer datos)
{
    InterfazJuego *interfaz = datos;
    EstadoEntrada estado;
    const char *mensaje;
    int numero;

    (void)widget;

    if (interfaz->juego.finalizado) {
        return;
    }

    estado = validar_entrada(
        gtk_entry_get_text(GTK_ENTRY(interfaz->entrada)),
        &numero
    );

    if (estado != ENTRADA_VALIDA) {
        mostrar_error_validacion(interfaz, estado);
        return;
    }

    mensaje = comprobar_numero(&interfaz->juego, numero);
    gtk_label_set_text(GTK_LABEL(interfaz->mensaje), mensaje);
    actualizar_contador(interfaz);

    if (interfaz->juego.finalizado) {
        finalizar_juego(interfaz);
    }
}

static void reiniciar_partida(GtkWidget *widget, gpointer datos)
{
    InterfazJuego *interfaz = datos;

    (void)widget;

    reiniciar_juego(&interfaz->juego);
    gtk_entry_set_text(GTK_ENTRY(interfaz->entrada), "");
    gtk_label_set_text(GTK_LABEL(interfaz->mensaje), "");
    actualizar_contador(interfaz);
    gtk_widget_set_sensitive(interfaz->entrada, TRUE);
    gtk_widget_set_sensitive(interfaz->boton_adivinar, TRUE);
    gtk_widget_grab_focus(interfaz->entrada);
}
