<?php

declare(strict_types=1);

session_start();

const NUMERO_MINIMO = 1;
const NUMERO_MAXIMO = 100;

// Reinicia todo el estado de la partida.
function reiniciarJuego(): void
{
    $_SESSION['numero_secreto'] = random_int(NUMERO_MINIMO, NUMERO_MAXIMO);
    $_SESSION['intentos'] = 0;
    $_SESSION['finalizado'] = false;
    $_SESSION['entrada'] = '';
    $_SESSION['mensaje'] = '';
}

// Valida la entrada antes de convertirla en un intento.
function validarEntrada(string $entrada): array
{
    $entrada = trim($entrada);

    if ($entrada === '') {
        return [null, 'Ingresa un número.'];
    }

    if (preg_match('/^[+-]?[0-9]+$/D', $entrada) !== 1) {
        return [null, 'Ingresa solamente números.'];
    }

    $numero = (int) $entrada;

    if ($numero < NUMERO_MINIMO || $numero > NUMERO_MAXIMO) {
        return [null, 'El número debe estar entre 1 y 100.'];
    }

    return [$numero, ''];
}

// Procesa la entrada y actualiza el juego cuando el intento es válido.
function procesarIntento(string $entrada): void
{
    if ($_SESSION['finalizado']) {
        return;
    }

    $_SESSION['entrada'] = $entrada;
    [$numero, $mensajeError] = validarEntrada($entrada);

    if ($mensajeError !== '') {
        $_SESSION['mensaje'] = $mensajeError;
        return;
    }

    $_SESSION['intentos']++;

    if ($numero < $_SESSION['numero_secreto']) {
        $_SESSION['mensaje'] = 'Muy bajo';
        return;
    }

    if ($numero > $_SESSION['numero_secreto']) {
        $_SESSION['mensaje'] = 'Muy alto';
        return;
    }

    $_SESSION['mensaje'] = '¡Correcto!';
    $_SESSION['finalizado'] = true;
}

if (!isset(
    $_SESSION['numero_secreto'],
    $_SESSION['intentos'],
    $_SESSION['finalizado'],
    $_SESSION['entrada'],
    $_SESSION['mensaje']
)) {
    reiniciarJuego();
}

if ($_SERVER['REQUEST_METHOD'] === 'POST') {
    $accion = is_string($_POST['accion'] ?? null) ? $_POST['accion'] : '';

    if ($accion === 'reiniciar') {
        reiniciarJuego();
    } elseif ($accion === 'adivinar') {
        $entrada = is_string($_POST['numero'] ?? null) ? $_POST['numero'] : '';
        procesarIntento($entrada);
    }

    header('Location: index.php', true, 303);
    exit;
}

$entrada = $_SESSION['entrada'];
$mensaje = $_SESSION['mensaje'];
$intentos = $_SESSION['intentos'];
$finalizado = $_SESSION['finalizado'];

?>
<!DOCTYPE html>
<html lang="es">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Adivina el Número</title>
    <link rel="stylesheet" href="style.css">
</head>
<body>
    <main class="juego">
        <h1>Adivina el Número</h1>
        <p class="instrucciones">Adivina un número del 1 al 100</p>

        <form method="post" action="index.php">
            <input
                type="text"
                name="numero"
                value="<?= htmlspecialchars($entrada, ENT_QUOTES | ENT_SUBSTITUTE, 'UTF-8') ?>"
                aria-label="Número del 1 al 100"
                autocomplete="off"
                autofocus
                <?= $finalizado ? 'disabled' : '' ?>
            >

            <button
                type="submit"
                name="accion"
                value="adivinar"
                <?= $finalizado ? 'disabled' : '' ?>
            >
                Adivinar
            </button>

            <p class="mensaje" aria-live="polite"><?= htmlspecialchars($mensaje, ENT_QUOTES | ENT_SUBSTITUTE, 'UTF-8') ?></p>
            <p class="intentos">Intentos: <?= $intentos ?></p>

            <button type="submit" name="accion" value="reiniciar" class="secundario">
                Reiniciar
            </button>
        </form>
    </main>
</body>
</html>
