"use strict";

const NUMERO_MINIMO = 1;
const NUMERO_MAXIMO = 100;

const formularioJuego = document.getElementById("formulario-juego");
const entradaNumero = document.getElementById("entrada-numero");
const botonAdivinar = document.getElementById("boton-adivinar");
const botonReiniciar = document.getElementById("boton-reiniciar");
const mensajeResultado = document.getElementById("mensaje-resultado");
const contadorIntentos = document.getElementById("contador-intentos");

let numeroSecreto;
let intentos;
let partidaTerminada;

function generarNumeroSecreto() {
    return Math.floor(Math.random() * 100) + 1;
}

function validarEntrada(texto) {
    const textoLimpio = texto.trim();

    if (textoLimpio === "") {
        return { numero: null, mensajeError: "Ingresa un número." };
    }

    if (!/^[+-]?\d+$/.test(textoLimpio)) {
        return { numero: null, mensajeError: "Ingresa solamente números." };
    }

    const numero = Number(textoLimpio);

    if (numero < NUMERO_MINIMO || numero > NUMERO_MAXIMO) {
        return {
            numero: null,
            mensajeError: "El número debe estar entre 1 y 100.",
        };
    }

    return { numero, mensajeError: null };
}

function adivinar(evento) {
    evento.preventDefault();

    if (partidaTerminada) {
        return;
    }

    const { numero, mensajeError } = validarEntrada(entradaNumero.value);

    if (mensajeError) {
        mensajeResultado.textContent = mensajeError;
        entradaNumero.focus();
        return;
    }

    intentos += 1;
    contadorIntentos.textContent = `Intentos: ${intentos}`;

    if (numero < numeroSecreto) {
        mensajeResultado.textContent = "Muy bajo";
    } else if (numero > numeroSecreto) {
        mensajeResultado.textContent = "Muy alto";
    } else {
        mensajeResultado.textContent = "¡Correcto!";
        partidaTerminada = true;
        entradaNumero.disabled = true;
        botonAdivinar.disabled = true;
        return;
    }

    entradaNumero.select();
    entradaNumero.focus();
}

function reiniciarJuego() {
    numeroSecreto = generarNumeroSecreto();
    intentos = 0;
    partidaTerminada = false;

    entradaNumero.value = "";
    entradaNumero.disabled = false;
    botonAdivinar.disabled = false;
    mensajeResultado.textContent = "";
    contadorIntentos.textContent = "Intentos: 0";
    entradaNumero.focus();
}

formularioJuego.addEventListener("submit", adivinar);
botonReiniciar.addEventListener("click", reiniciarJuego);

reiniciarJuego();
