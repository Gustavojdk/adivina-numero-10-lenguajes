import tkinter as tk

from ui import InterfazJuego


def main():
    ventana = tk.Tk()
    InterfazJuego(ventana)
    ventana.mainloop()


if __name__ == "__main__":
    main()
