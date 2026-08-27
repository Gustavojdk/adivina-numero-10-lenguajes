import tkinter as tk

from game import JuegoAdivinaNumero, NUMERO_MAXIMO, NUMERO_MINIMO


def validar_entrada(texto):
    texto = texto.strip()

    if not texto:
        return None, "Ingresa un número."

    try:
        numero = int(texto)
    except ValueError:
        return None, "Ingresa solamente números."

    if numero < NUMERO_MINIMO or numero > NUMERO_MAXIMO:
        return None, "El número debe estar entre 1 y 100."

    return numero, None


class InterfazJuego:
    def __init__(self, ventana):
        self.ventana = ventana
        self.juego = JuegoAdivinaNumero()

        self.ventana.title("Adivina el Número")
        self.ventana.resizable(False, False)

        self._crear_componentes()
        self.entrada.focus_set()

    def _crear_componentes(self):
        contenedor = tk.Frame(self.ventana, padx=24, pady=20)
        contenedor.pack()

        titulo = tk.Label(
            contenedor,
            text="Adivina el Número",
            font=("Arial", 16, "bold"),
        )
        titulo.pack(pady=(0, 8))

        instrucciones = tk.Label(
            contenedor,
            text="Adivina un número del 1 al 100",
        )
        instrucciones.pack(pady=(0, 12))

        self.entrada = tk.Entry(contenedor, width=18, justify="center")
        self.entrada.pack(pady=(0, 10))
        self.entrada.bind("<Return>", self.adivinar)

        self.boton_adivinar = tk.Button(
            contenedor,
            text="Adivinar",
            width=14,
            command=self.adivinar,
        )
        self.boton_adivinar.pack(pady=(0, 12))

        self.mensaje_resultado = tk.Label(contenedor, text="", width=34)
        self.mensaje_resultado.pack(pady=(0, 8))

        self.etiqueta_intentos = tk.Label(contenedor, text="Intentos: 0")
        self.etiqueta_intentos.pack(pady=(0, 12))

        boton_reiniciar = tk.Button(
            contenedor,
            text="Reiniciar",
            width=14,
            command=self.reiniciar,
        )
        boton_reiniciar.pack()

    def adivinar(self, evento=None):
        numero, mensaje_error = validar_entrada(self.entrada.get())

        if mensaje_error:
            self.mensaje_resultado.config(text=mensaje_error)
            self.entrada.focus_set()
            return

        resultado = self.juego.comprobar_numero(numero)
        self.mensaje_resultado.config(text=resultado)
        self.etiqueta_intentos.config(text=f"Intentos: {self.juego.intentos}")

        if resultado == "¡Correcto!":
            self.entrada.config(state="disabled")
            self.boton_adivinar.config(state="disabled")
        else:
            self.entrada.select_range(0, tk.END)
            self.entrada.focus_set()

    def reiniciar(self):
        self.juego.reiniciar()

        self.entrada.config(state="normal")
        self.entrada.delete(0, tk.END)
        self.boton_adivinar.config(state="normal")
        self.mensaje_resultado.config(text="")
        self.etiqueta_intentos.config(text="Intentos: 0")
        self.entrada.focus_set()
