package main

import "math/rand/v2"

const (
	NumeroMinimo = 1
	NumeroMaximo = 100
)

// Juego mantiene la lógica y el estado de una partida.
type Juego struct {
	numeroSecreto int
	Intentos      int
	finalizado    bool
}

func NuevoJuego() *Juego {
	juego := &Juego{}
	juego.Reiniciar()
	return juego
}

func (j *Juego) ComprobarNumero(numero int) string {
	if j.finalizado || numero < NumeroMinimo || numero > NumeroMaximo {
		return ""
	}

	j.Intentos++

	switch {
	case numero < j.numeroSecreto:
		return "Muy bajo"
	case numero > j.numeroSecreto:
		return "Muy alto"
	default:
		j.finalizado = true
		return "¡Correcto!"
	}
}

func (j *Juego) Reiniciar() {
	j.numeroSecreto = rand.IntN(NumeroMaximo-NumeroMinimo+1) + NumeroMinimo
	j.Intentos = 0
	j.finalizado = false
}

func (j *Juego) Finalizado() bool {
	return j.finalizado
}
