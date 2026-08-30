package main

import (
	"regexp"
	"strconv"
	"strings"

	"fyne.io/fyne/v2"
	"fyne.io/fyne/v2/app"
	"fyne.io/fyne/v2/container"
	"fyne.io/fyne/v2/widget"
)

var patronEntero = regexp.MustCompile(`^[+-]?[0-9]+$`)

func main() {
	aplicacion := app.New()
	ventana := aplicacion.NewWindow("Adivina el Número")
	juego := NuevoJuego()

	titulo := widget.NewLabelWithStyle(
		"Adivina el Número",
		fyne.TextAlignCenter,
		fyne.TextStyle{Bold: true},
	)
	instrucciones := widget.NewLabelWithStyle(
		"Adivina un número del 1 al 100",
		fyne.TextAlignCenter,
		fyne.TextStyle{},
	)
	entrada := widget.NewEntry()
	entrada.SetPlaceHolder("Número del 1 al 100")
	resultado := widget.NewLabel("")
	resultado.Alignment = fyne.TextAlignCenter
	intentos := widget.NewLabel("Intentos: 0")
	intentos.Alignment = fyne.TextAlignCenter

	var botonAdivinar *widget.Button
	botonAdivinar = widget.NewButton("Adivinar", func() {
		procesarIntento(juego, entrada, botonAdivinar, resultado, intentos)
	})
	entrada.OnSubmitted = func(string) {
		procesarIntento(juego, entrada, botonAdivinar, resultado, intentos)
	}
	botonReiniciar := widget.NewButton("Reiniciar", func() {
		reiniciarJuego(juego, entrada, botonAdivinar, resultado, intentos)
	})

	contenido := container.NewVBox(
		titulo,
		instrucciones,
		entrada,
		botonAdivinar,
		resultado,
		intentos,
		botonReiniciar,
	)

	ventana.SetContent(container.NewPadded(contenido))
	ventana.Resize(fyne.NewSize(380, 320))
	ventana.ShowAndRun()
}

func procesarIntento(
	juego *Juego,
	entrada *widget.Entry,
	botonAdivinar *widget.Button,
	resultado *widget.Label,
	intentos *widget.Label,
) {
	if juego.Finalizado() {
		return
	}

	numero, mensajeError := validarEntrada(entrada.Text)
	if mensajeError != "" {
		resultado.SetText(mensajeError)
		return
	}

	mensaje := juego.ComprobarNumero(numero)
	resultado.SetText(mensaje)
	intentos.SetText("Intentos: " + strconv.Itoa(juego.Intentos))

	if mensaje == "¡Correcto!" {
		finalizarJuego(entrada, botonAdivinar)
	}
}

func validarEntrada(texto string) (int, string) {
	entrada := strings.TrimSpace(texto)

	if entrada == "" {
		return 0, "Ingresa un número."
	}

	if !patronEntero.MatchString(entrada) {
		return 0, "Ingresa solamente números."
	}

	numero, errorConversion := strconv.Atoi(entrada)
	if errorConversion != nil || numero < NumeroMinimo || numero > NumeroMaximo {
		return 0, "El número debe estar entre 1 y 100."
	}

	return numero, ""
}

func finalizarJuego(entrada *widget.Entry, botonAdivinar *widget.Button) {
	entrada.Disable()
	botonAdivinar.Disable()
}

func reiniciarJuego(
	juego *Juego,
	entrada *widget.Entry,
	botonAdivinar *widget.Button,
	resultado *widget.Label,
	intentos *widget.Label,
) {
	juego.Reiniciar()
	entrada.Enable()
	botonAdivinar.Enable()
	entrada.SetText("")
	resultado.SetText("")
	intentos.SetText("Intentos: 0")
}
