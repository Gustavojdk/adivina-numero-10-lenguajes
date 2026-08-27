import random


NUMERO_MINIMO = 1
NUMERO_MAXIMO = 100


class JuegoAdivinaNumero:
    """Guarda el estado y contiene la lógica del juego."""

    def __init__(self):
        self.numero_secreto = 0
        self.intentos = 0
        self.reiniciar()

    def comprobar_numero(self, numero):
        if not isinstance(numero, int) or isinstance(numero, bool):
            raise ValueError("El intento debe ser un número entero.")

        if numero < NUMERO_MINIMO or numero > NUMERO_MAXIMO:
            raise ValueError("El número debe estar entre 1 y 100.")

        self.intentos += 1

        if numero < self.numero_secreto:
            return "Muy bajo"

        if numero > self.numero_secreto:
            return "Muy alto"

        return "¡Correcto!"

    def reiniciar(self):
        self.numero_secreto = random.randint(NUMERO_MINIMO, NUMERO_MAXIMO)
        self.intentos = 0
